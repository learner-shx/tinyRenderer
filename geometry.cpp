#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>
#include "geometry.h"

void swap(double& a, double& b)
{
    int t = a;
    a = b;
    b = t;
    return;
}

Matrix::Matrix(int r, int c):
m(std::vector<std::vector<double>>(r, std::vector(c, 0.))),
cols(c), rows(r)
{

}

int Matrix::ncols()
{
    return cols;
} 

int Matrix::nrows()
{
    return rows;
}

std::vector<double>& Matrix::operator[](const int n)
{
    assert(n>=0 && n <=rows);
    return m[n];
}

Matrix Matrix::operator= (std::initializer_list< double > str)
{
    assert((unsigned)rows * (unsigned)cols == str.size());
    int i = 0;
    int j = 0;
    for(auto it = str.begin(); it != str.end(); ++it)
    {
        m[i][j] = *it;
        if(j < cols) 
            j++;
        if(i < rows && j == cols)
        {
            i++;
            j = 0;
        }
    }
    return *this;
}

Matrix Matrix::operator=(const Matrix& mat)
{
    assert(cols == mat.cols && rows == mat.rows);
    m = mat.m;
    return mat;
}

Matrix Matrix::operator*(const Matrix& a)
{
    assert(cols == a.rows);
    Matrix ans(rows, a.cols);
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < a.cols; j++)
        {
            ans.m[i][j] = 0.;
            for(int k = 0; k < cols; k++)
                ans.m[i][j] += m[i][k] * a.m[k][j];
        }
    return ans;
}

Vec3f Matrix::operator* (const Vec3f& v)
{
    assert(cols == rows && cols == 3);
    Vec3f ans(0,0,0);
    ans.x = m[0][0]* v.x + m[0][1] * v.y + m[0][2] * v.z;
    ans.y = m[1][0]* v.x + m[1][1] * v.y + m[1][2] * v.z;
    ans.z = m[2][0]* v.x + m[2][1] * v.y + m[2][2] * v.z;
    return ans;
}

Vec4f Matrix::operator* (const Vec4f& v)
{
    assert(cols == rows && cols == 4);
    Vec4f ans(0,0,0,0);
    ans.x = m[0][0]* v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
    ans.y = m[1][0]* v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
    ans.z = m[2][0]* v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
    ans.z = m[3][0]* v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;
    return ans;
}

Matrix Matrix::transpose()
{
    Matrix ans(rows, cols);
    for(int i = 0; i<rows; i++)
        for(int j = 0; j < cols; j++)
            ans[i][j] = m[j][i];
    return ans;
}

std::ostream& operator<<(std::ostream& s, Matrix& m) {
    for (int i=0; i<m.nrows(); i++)  {
        for (int j=0; j<m.ncols(); j++) {
            s << m[i][j];
            if (j<m.ncols()-1) s << "\t";
        }
        s << "\n";
    }
    return s;
}

Matrix Matrix::inverse()
{
    assert(rows == cols);
    //initialization
    Matrix ans(rows, cols * 2);

    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            ans[i][j] = m[i][j];
    
    for(int i = 0; i < rows; i++)
        ans[i][i + cols] = 1;
    
    // std::cout<<ans;
    // up triangulation
    //beacuse transform ith col step need i + 1, so rows - 1
    for(int i = 0; i< rows - 1; i++)
    {
        //normalize the ith row
        if(ans[i][i] == 0)
        {
            int t = i;
            while(!ans[t][i])
                t++;
            for(int j = 0; j < ans.cols; j++)
                swap(ans[t][j], ans[i][j]);
        }
        // to avoid ans[i][i] first become 1, reverse the sequence
        for(int j = cols * 2 - 1; j >= 0; j--)
        {
            ans[i][j] /= ans[i][i];
            // std::cout<<ans[i][i]<<std::endl;
        }

        //transform ith col into 0
        for(int k = i + 1; k < rows; k++)
        {
            double coeff = ans[k][i];
            for(int j = 0; j < ans.cols; j++)
                ans[k][j] -= coeff * ans[i][i];  
        }
    }

    // finish the last rows
    for(int j = ans.cols - 1; j >= rows - 1; j--)
        ans[rows - 1][j] /= ans[rows - 1][rows - 1];
    

    //down triangulation
    for(int i = rows - 1; i >= 0; i--)
    {
        for(int k = i - 1; k >= 0; k--)
        {
            double coeff = ans[k][i];
            for(int j = i; j < ans.cols; j++)
                ans[k][j] -= ans[i][j] * coeff;
        }
    }

    //cut identity matrix
    Matrix result(rows, cols);
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            result[i][j] = ans[i][j+cols];
    
    return result;
}

Matrix Matrix::mat3to4()
{
    assert(rows == 3 && cols == 3);
    Matrix ans(4, 4);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            ans.m[i][j] = m[i][j];
    
    for(int i = 0; i < 4; i++)
        ans.m[i][3] = 0;
    for(int j = 0; j < 4; j++)
        ans.m[3][j] = 0;
    ans.m[3][3] = 1;
    return ans;
}
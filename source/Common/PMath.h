///////////////////////////////////////////////////////////////////////////////////////////////////
//	Author: Christopher Sosa																	 //
//																								 //
//	This is an implementaion of a scalar vector math library for use in the						 //
//	Photon game/graphics engine.															     //
//																								 //
//	Majority of implementation inspired by Nathan Reed's blog						             //
//	On Vector Math Libraries	                                                                 //
//	http://www.reedbeta.com/blog/2013/12/28/on-vector-math-libraries/						     //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PMATH_H
#define PMATH_H

#include <math.h>

namespace PMath
{
	const float PI = 3.14159265359f;     //180 degrees
	const float TWOPI = PI * 2.0f;       //360 degrees
	const float PIOVERTWO = PI * 0.5f;   //90 degrees
	const float PIOVERFOUR = PI * 0.25f; //45 degrees


	// Templated by type and size Vector
	template<typename T, int n>
	struct Vector 
	{ 
		// Vector Data
		T data[n];

		T& operator[](unsigned int component) { return data[component]; };
		const T& operator[](unsigned int component) const { return data[component]; }

		// Vector Addition and Subtraction
		Vector<T, n>& operator+=(const Vector<T, n>& rhs)
		{
			for (int i = 0; i < n; i++)
			{
				data[i] += rhs[i];
			}

			return *this;
		}
		Vector<T, n>& operator-=(const Vector<T, n>& rhs)
		{
			for (int i = 0; i < n; i++)
			{
				data[i] -= rhs[i];
			}

			return *this;
		}

		// Vector Multiplication by scalar
		Vector<T, n>& operator*=(const T& scalar)
		{
			for (int i = 0; i < n; i++)
			{
				data[i] *= scalar;
			}

			return *this;
		}
		Vector<T, n>& operator/=(const T& scalar)
		{
			for (int i = 0; i < n; i++)
			{
				data[i] /= scalar;
			}

			return *this;
		}
	};

	// Common Vector typedefs
	typedef Vector<float, 2> Vec2;
	typedef Vector<float, 3> Vec3;
	typedef Vector<float, 4> Vec4;

	// Partial Vector specializations with .x .y .z .w .r .b etc.. access
	template<typename T>
	struct Vector<T, 2>
	{
		union
		{
			T data[2];
			struct { T x, y; };
			struct { T r, g; };
		};

		// Constructors
		Vector() : x(0), y(0) {}
		Vector(T x, T y) : x(x), y(y) {}
		explicit Vector(T value) : x(value), y(value) {}
		T& operator[](unsigned int component) { return data[component]; }
		const T& operator[](unsigned int component) const { return data[component]; }
		Vector<T, 2>& operator+=(const Vector<T, 2>& rhs)
		{
			for (int i = 0; i < 2; i++)
			{
				data[i] += rhs[i];
			}

			return *this;
		}
		Vector<T, 2>& operator-=(const Vector<T, 2>& rhs)
		{
			for (int i = 0; i < 2; i++)
			{
				data[i] -= rhs[i];
			}

			return *this;
		}
		Vector<T, 2>& operator*=(const T& scalar)
		{
			for (int i = 0; i < 2; i++)
			{
				data[i] *= scalar;
			}

			return *this;
		}
		Vector<T, 2>& operator/=(const T& scalar)
		{
			for (int i = 0; i < 2; i++)
			{
				data[i] /= scalar;
			}

			return *this;
		}
	};

	template<typename T>
	struct Vector<T, 3>
	{
		union
		{
			T data[3];
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		// Constructors
		Vector() : x(0), y(0), z(0) {}
		Vector(T x, T y, T z) : x(x), y(y), z(z) {}
		explicit Vector(T value) : x(value), y(value), z(value) {}
		Vector(Vec2& xy, T z) : x(xy.x), y(xy.y), z(z) {}
		T& operator[](unsigned int component) { return data[component]; }
		const T& operator[](unsigned int component) const { return data[component]; }
		Vector<T, 3>& operator+=(const Vector<T, 3>& rhs)
		{
			for (int i = 0; i < 3; i++)
			{
				data[i] += rhs[i];
			}

			return *this;
		}
		Vector<T, 3>& operator-=(const Vector<T, 3>& rhs)
		{
			for (int i = 0; i < 3; i++)
			{
				data[i] -= rhs[i];
			}

			return *this;
		}
		Vector<T, 3>& operator*=(const T& scalar)
		{
			for (int i = 0; i < 3; i++)
			{
				data[i] *= scalar;
			}

			return *this;
		}
		Vector<T, 3>& operator/=(const T& scalar)
		{
			for (int i = 0; i < 3; i++)
			{
				data[i] /= scalar;
			}

			return *this;
		}
	};

	template<typename T>
	struct Vector<T, 4>
	{
		union
		{
			T data[4];
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
		};

		// Constructors
		Vector() : x(0), y(0), z(0), w(0) {}
		Vector(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
		explicit Vector(T value) : x(value), y(value), z(value), w(value) {}
		Vector(Vector<T, 2>& xy, T z, T w) : x(xy.x), y(xy.y), z(z), w(w) {}
		Vector(Vector<T, 3>& xyz, T w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
		T& operator[](unsigned int component) { return data[component]; }
		const T& operator[](unsigned int component) const { return data[component]; }
		Vector<T, 4>& operator+=(const Vector<T, 4>& rhs)
		{
			for (int i = 0; i < 4; i++)
			{
				data[i] += rhs[i];
			}

			return *this;
		}
		Vector<T, 4>& operator-=(const Vector<T, 4>& rhs)
		{
			for (int i = 0; i < 4; i++)
			{
				data[i] -= rhs[i];
			}

			return *this;
		}
		Vector<T, 4>& operator*=(const T& scalar)
		{
			for (int i = 0; i < 4; i++)
			{
				data[i] *= scalar;
			}

			return *this;
		}
		Vector<T, 4>& operator/=(const T& scalar)
		{
			for (int i = 0; i < 4; i++)
			{
				data[i] /= scalar;
			}

			return *this;
		}
	};

	// Commonly used vectors
	static const Vec3 Zero = Vec3();
	static const Vec3 Forward = Vec3(0.0f, 0.0f, 1.0f);
	static const Vec3 Up = Vec3(0.0f, 1.0f, 0.0f);
	static const Vec3 Right = Vec3(1.0f, 0.0f, 0.0f);

	// Templated by type and size Matrix
	template<typename T, int rows, int cols>
	struct Matrix
	{
		T data[rows][cols];

		Matrix<T, rows, cols>& operator*=(const T& scalar)
		{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					data[i][j] *= scalar;
				}
			}

			return *this;
		}

		Matrix<T, rows, cols>& operator/=(const T& scalar)
		{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					data[i][j] /= scalar;
				}
			}

			return *this;
		}
	};

	// Partial Matrix specializations with .m00 .m01 .row1 .row2 etc.. access
	template<typename T>
	struct Matrix<T, 3, 3>
	{
		union
		{
			T data[3][3];
			struct
			{
				T m00, m01, m02,
				  m10, m11, m12,
				  m20, m21, m22;
			};
			struct { Vector<T, 3> row0, row1, row2; };
			struct { Vector<T, 3> rows[3]; };
		};
		Matrix() 
		: m00(0), m01(0), m02(0), m10(0), m11(0), m12(0), m20(0), m21(0), m22(0) {}
		Matrix(T M00, T M01, T M02, T M10, T M11, T M12, T M20, T M21, T M22)
		{
			data[0][0] = M00; data[0][1] = M01; data[0][2] = M02;
			data[1][0] = M10; data[1][1] = M11; data[1][2] = M12;
			data[2][0] = M20; data[2][1] = M21; data[2][2] = M22;
		}
		//Matrix(Vector<T, 3>& Row0, Vector<T, 3>& Row1, Vector<T, 3>& Row2) : row0(Row0), row1(Row1), row2(Row2) {}
		Vector<T, 3>& operator[](unsigned int n) { return rows[n]; }

		Matrix<T, 3, 3>& operator*=(const T& scalar)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					data[i][j] *= scalar;
				}
			}

			return *this;
		}

		Matrix<T, 3, 3>& operator/=(const T& scalar)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					data[i][j] /= scalar;
				}
			}

			return *this;
		}
	};

	template<typename T>
	struct Matrix<T, 4, 4>
	{
		union
		{
			T data[4][4];
			struct
			{
				T m00, m01, m02, m03,
				  m10, m11, m12, m13,
				  m20, m21, m22, m23,
				  m30, m31, m32, m33;
			};
			struct { Vector<T, 4> row0, row1, row2, row3; };
			struct { Vector<T, 4> rows[4]; };
		};
		Matrix()
		: m00(0), m01(0), m02(0), m03(0), m10(0), m11(0), m12(0), m13(0),
		  m20(0), m21(0), m22(0), m23(0), m30(0), m31(0), m32(0), m33(0) {}
		Matrix(T M00, T M01, T M02, T M03, T M10, T M11, T M12, T M13,
			   T M20, T M21, T M22, T M23, T M30, T M31, T M32, T M33)
		{
			data[0][0] = M00; data[0][1] = M01; data[0][2] = M02; data[0][3] = M03;
			data[1][0] = M10; data[1][1] = M11; data[1][2] = M12; data[1][3] = M13;
			data[2][0] = M20; data[2][1] = M21; data[2][2] = M22; data[2][3] = M23;
			data[3][0] = M30; data[3][1] = M31; data[3][2] = M32; data[3][3] = M33;
		}
		//Matrix(Vector<T, 4>& Row0, Vector<T, 4>& Row1, Vector<T, 4>& Row2, Vector<T, 4>& Row3) : row0(Row0), row1(Row1), row2(Row2), row3(Row3) {}
		Vector<T, 4>& operator[](unsigned int n) { return rows[n]; }

		Matrix<T, 4, 4>& operator*=(const T& scalar)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					data[i][j] *= scalar;
				}
			}

			return *this;
		}

		Matrix<T, 4, 4>& operator/=(const T& scalar)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					data[i][j] /= scalar;
				}
			}

			return *this;
		}
	};

	// Common Matrix typedefs
	typedef Matrix<float, 3, 3> Mat3x3;
	typedef Matrix<float, 4, 4> Mat4x4;

	// Creation Functions
	inline Mat3x3 CreateRowMatrix3x3(Vec3& rowX, Vec3& rowY, Vec3& rowZ)
	{
		Mat3x3 m;
		m.row0 = rowX;
		m.row1 = rowY;
		m.row2 = rowZ;

		return m;
	}

	inline Mat3x3 CreateColumnMatrix3x3(Vec3& columnX, Vec3& columnY, Vec3& columZ)
	{
		return Mat3x3(columnX.x, columnY.x, columZ.x, 
			          columnX.y, columnY.y, columZ.y, 
					  columnX.z, columnY.z, columZ.z);
	}

	inline Mat3x3 CreateIdentity3x3()
	{
		return Mat3x3(1.0f, 0, 0,
					  0, 1.0f, 0,
					  0, 0, 1.0f);
	}

	inline Mat4x4 CreateRowMatrix4x4(Vec4& rowX, Vec4& rowY, Vec4& rowZ, Vec4& rowW)
	{
		Mat4x4 m;
		m.row0 = rowX;
		m.row1 = rowY;
		m.row2 = rowZ;
		m.row3 = rowW;

		return m;
	}

	inline Mat4x4 CreateColumnMatrix4x4(Vec4& columnX, Vec4& columnY, Vec4& columnZ, Vec4& columnW)
	{
		return Mat4x4(columnX.x, columnY.x, columnZ.x, columnW.x, 
			          columnX.y, columnY.y, columnZ.y, columnW.y,
			          columnX.z, columnY.z, columnZ.z, columnW.z,
					  columnX.w, columnY.w, columnZ.w, columnW.w);
	}

	inline Mat4x4 CreateIdentity4x4()
	{
		return Mat4x4(1.0f, 0, 0, 0,
					  0, 1.0f, 0, 0,
					  0, 0, 1.0f, 0,
					  0, 0, 0, 1.0f);
	}

	// This is a left handed rotation column matrix which rotates about the X axis.
	inline Mat4x4 MatrixRotationX(float angle)
	{
		float sinOfAngle = sin(angle);
		float cosOfAngle = cos(angle);

		return Mat4x4(1, 0,           0,          0,
			          0, cosOfAngle,  sinOfAngle, 0,
			          0, -sinOfAngle, cosOfAngle, 0,
			          0, 0,           0,          1);
	}

	// This is a left handed rotation column matrix which rotates about the Y axis.
	inline Mat4x4 MatrixRotationY(float angle)
	{
		float sinOfAngle = sin(angle);
		float cosOfAngle = cos(angle);

		return Mat4x4(cosOfAngle, 0, -sinOfAngle, 0,
			          0,          1, 0,           0,
					  sinOfAngle, 0, cosOfAngle,  0,
			          0,          0, 0,           1);
	}

	// This is a left handed rotation column matrix which rotates about the Z axis.
	inline Mat4x4 MatrixRotationZ(float angle)
	{
		float sinOfAngle = sin(angle);
		float cosOfAngle = cos(angle);

		return Mat4x4(cosOfAngle,  sinOfAngle, 0, 0,
			          -sinOfAngle, cosOfAngle, 0, 0,
			          0,           0,          1, 0,
			          0,           0,          0, 1);
	}

	// Vector operations
	template<typename T, int size>
	Vector<T, size> Add(Vector<T, size>& lhs, const Vector<T, size>& rhs)
	{
		return lhs += rhs;
	}

	template<typename T, int size>
	Vector<T, size> operator+(Vector<T, size>& lhs, const Vector<T, size>& rhs)
	{
		return Add(lhs, rhs);
	}

	template<typename T, int size>
	Vector<T, size> Sub(Vector<T, size>& lhs, const Vector<T, size>& rhs)
	{
		return lhs -= rhs;
	}

	template<typename T, int size>
	Vector<T, size> operator-(Vector<T, size>& lhs, const Vector<T, size>& rhs)
	{
		return Sub(lhs, rhs);
	}

	template<typename T, int size>
	Vector<T, size> operator*(Vector<T, size>& lhs, const T& scalar)
	{
		return lhs *= scalar;
	}

	template<typename T, int size>
	Vector<T, size> operator/(Vector<T, size>& lhs, const T& scalar)
	{
		return lhs /= scalar;
	}

	template<typename T, int size>
	inline T LengthSquared(Vector<T, size>& v)
	{
		T result = 0;
		for (int i = 0; i < size; i++)
		{
			result += (v[i] * v[i]);
		}

		return result;
	}

	template<typename T, int size>
	inline T Length(Vector<T, size>& v)
	{
		return sqrtf(LengthSquared<T, size>(v));
	}

	template<typename T, int size>
	inline Vector<T, size> Normalize(Vector<T, size>& v)
	{
		T length = Length<T, size>(v);

		if (length > 0)
		{
			for (int i = 0; i < size; i++)
			{
				v[i] /= length;
			}
		}

		return v;
	}

	template<typename T, int size>
	inline T Dot(const Vector<T, size>& lhs, const Vector<T, size>& rhs)
	{
		T result = 0;
		for (int i = 0; i < size; i++)
		{
			result += (lhs[i] * rhs[i]);
		}

		return result;
	}

	inline Vec3 Cross(Vec3& lhs, Vec3& rhs)
	{
		return Vec3((lhs.y*rhs.z) - (lhs.z*rhs.y), (lhs.z*rhs.x) - (lhs.x*rhs.z), (lhs.x*rhs.y) - (lhs.y*rhs.x));
	}

	// Matrix operations
	template<typename T, int rows, int cols>
	Matrix<T, rows, cols> operator*(Matrix<T, rows, cols>& lhs, const T& scalar)
	{
		return lhs *= scalar;
	}

	template<typename T, int rows, int cols>
	Matrix<T, rows, cols> operator/(Matrix<T, rows, cols>& lhs, const T& scalar)
	{
		return lhs /= scalar;
	}

	template<typename T, int N, int M, int O>
	Matrix<T, N, O> operator*(const Matrix<T, N, M>& lhs, const Matrix<T, M, O>& rhs)
	{
		T sum = 0;
		Matrix<T, N, O> m;

		int i, j, k;
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < M; j++)
			{
				for (k = 0; k < M; k++)
				{
					sum += lhs.data[i][k] * rhs.data[k][j];
				}
				m.data[i][j] = sum;
				sum = 0;
			}
		}

		return m;
	}

	//Row vector * Matrix
	template<typename T, int rows, int cols>
	Vector<T, rows> operator*(const Vector<T, rows>& v, const Matrix<T, rows, cols>& m)
	{
		Vector<T, rows> result;
		T sum = 0;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				sum += v[j] * m.data[j][i];
			}
			result[i] = sum;
			sum = 0;
		}

		return result;
	}

	//Matrix * Column Vector
	template<typename T, int rows, int cols>
	Vector<T, cols> operator*(const Matrix<T, rows, cols>& m, const Vector<T, cols>& v)
	{
		Vector<T, cols> result;
		T sum = 0;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				sum += m.data[i][j] * v[j];
			}
			result[i] = sum;
			sum = 0;
		}

		return result;
	}

	template<typename T, int rows, int cols>
	Matrix<T, cols, rows> Transpose(const Matrix<T, rows, cols>& m)
	{
		Matrix<T, cols, rows> mT;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				mT.data[i][j] = m.data[j][i];
			}
		}

		return mT;
	}

	inline float Determinant(const Mat3x3& m)
	{
		return m.m00*(m.m11*m.m22 - m.m12*m.m21) + m.m01*(m.m12*m.m20 - m.m10*m.m22) + m.m02*(m.m10*m.m21 - m.m11*m.m20);
	}

	inline float Determinant(const Mat4x4& m)
	{
		float det = 0;
		det += m.m00*(m.m11*(m.m22*m.m33 - m.m23*m.m32) + m.m12*(m.m23*m.m31 - m.m21*m.m33) + m.m13*(m.m21*m.m32 - m.m22*m.m31));
		det += (-m.m01*(m.m10*(m.m22*m.m33 - m.m23*m.m32) + m.m12*(m.m23*m.m30 - m.m20*m.m33) + m.m13*(m.m20*m.m32 - m.m22*m.m30)));
		det += m.m02*(m.m10*(m.m21*m.m33 - m.m23*m.m31) + m.m11*(m.m23*m.m30 - m.m20*m.m33) + m.m13*(m.m20*m.m31 - m.m21*m.m30));
		det += (-m.m03*(m.m10*(m.m21*m.m32 - m.m22*m.m31) + m.m11*(m.m22*m.m30 - m.m20*m.m32) + m.m12*(m.m20*m.m31 - m.m21*m.m30)));
		return det;
	}

	inline Mat3x3 Inverse(const Mat3x3& m)
	{
		// Determinant inverse to lower the amount of divisions
		float oneOverDeterminant = 1/Determinant(m);
		Mat3x3 mInverse;

		//Matrix of Cofactors
		mInverse.m00 = ((m.m11 * m.m22) - (m.m12 * m.m21))*oneOverDeterminant;
		mInverse.m01 = ((m.m12 * m.m20) - (m.m10 * m.m22))*oneOverDeterminant;
		mInverse.m02 = ((m.m10 * m.m21) - (m.m11 * m.m20))*oneOverDeterminant;
		mInverse.m10 = ((m.m02 * m.m21) - (m.m01 * m.m22))*oneOverDeterminant;
		mInverse.m11 = ((m.m00 * m.m22) - (m.m02 * m.m20))*oneOverDeterminant;
		mInverse.m12 = ((m.m01 * m.m20) - (m.m00 * m.m21))*oneOverDeterminant;
		mInverse.m20 = ((m.m01 * m.m12) - (m.m02 * m.m11))*oneOverDeterminant;
		mInverse.m21 = ((m.m02 * m.m10) - (m.m00 * m.m12))*oneOverDeterminant;
		mInverse.m22 = ((m.m00 * m.m11) - (m.m01 * m.m10))*oneOverDeterminant;

		return Transpose<float, 3, 3>(mInverse);
	}

	inline Mat4x4 Inverse(const Mat4x4& m)
	{
		// Determinant inverse to lower the amount of divisions.
		float oneOverDeterminant = 1 / Determinant(m);
		Mat4x4 mInverse;

		//Matrix of Cofactors
		mInverse.m00 = (m.m11*(m.m22*m.m33 - m.m23*m.m32) + m.m12*(m.m23*m.m31 - m.m21*m.m33) + m.m13*(m.m21*m.m32 - m.m22*m.m31))*oneOverDeterminant;
		mInverse.m01 = -(m.m10*(m.m22*m.m33 - m.m23*m.m32) + m.m12*(m.m23*m.m30 - m.m20*m.m33) + m.m13*(m.m20*m.m32 - m.m22*m.m30))*oneOverDeterminant;
		mInverse.m02 = (m.m10*(m.m21*m.m33 - m.m23*m.m31) + m.m11*(m.m23*m.m30 - m.m20*m.m33) + m.m13*(m.m20*m.m31 - m.m21*m.m30))*oneOverDeterminant;
		mInverse.m03 = -(m.m10*(m.m21*m.m32 - m.m22*m.m31) + m.m11*(m.m22*m.m30 - m.m20*m.m32) + m.m12*(m.m20*m.m31 - m.m21*m.m30))*oneOverDeterminant;
		mInverse.m10 = -(m.m01*(m.m22*m.m33 - m.m23*m.m32) + m.m02*(m.m23*m.m31 - m.m21*m.m33) + m.m03*(m.m21*m.m32 - m.m22*m.m31))*oneOverDeterminant;
		mInverse.m11 = (m.m00*(m.m22*m.m33 - m.m23*m.m32) + m.m02*(m.m23*m.m30 - m.m20*m.m33) + m.m03*(m.m20*m.m32 - m.m22*m.m30))*oneOverDeterminant;
		mInverse.m12 = -(m.m00*(m.m21*m.m33 - m.m23*m.m31) + m.m01*(m.m23*m.m30 - m.m20*m.m33) + m.m03*(m.m20*m.m31 - m.m21*m.m30))*oneOverDeterminant;
		mInverse.m13 = (m.m00*(m.m21*m.m32 - m.m22*m.m31) + m.m01*(m.m22*m.m30 - m.m20*m.m32) + m.m02*(m.m20*m.m31 - m.m21*m.m30))*oneOverDeterminant;
		mInverse.m20 = (m.m01*(m.m12*m.m33 - m.m13*m.m32) + m.m02*(m.m13*m.m31 - m.m11*m.m33) + m.m03*(m.m11*m.m32 - m.m12*m.m31))*oneOverDeterminant;
		mInverse.m21 = -(m.m00*(m.m12*m.m33 - m.m13*m.m32) + m.m02*(m.m13*m.m30 - m.m10*m.m33) + m.m03*(m.m10*m.m32 - m.m12*m.m30))*oneOverDeterminant;
		mInverse.m22 = (m.m00*(m.m11*m.m33 - m.m13*m.m31) + m.m01*(m.m13*m.m30 - m.m10*m.m33) + m.m03*(m.m10*m.m31 - m.m11*m.m30))*oneOverDeterminant;
		mInverse.m23 = -(m.m00*(m.m11*m.m32 - m.m12*m.m31) + m.m01*(m.m12*m.m30 - m.m10*m.m32) + m.m02*(m.m10*m.m31 - m.m11*m.m30))*oneOverDeterminant;
		mInverse.m30 = -(m.m01*(m.m12*m.m23 - m.m13*m.m22) + m.m02*(m.m13*m.m21 - m.m11*m.m23) + m.m03*(m.m11*m.m22 - m.m12*m.m21))*oneOverDeterminant;
		mInverse.m31 = (m.m00*(m.m12*m.m23 - m.m13*m.m22) + m.m02*(m.m13*m.m20 - m.m10*m.m23) + m.m03*(m.m10*m.m22 - m.m12*m.m20))*oneOverDeterminant;
		mInverse.m32 = -(m.m00*(m.m11*m.m23 - m.m13*m.m21) + m.m01*(m.m13*m.m20 - m.m10*m.m23) + m.m03*(m.m10*m.m21 - m.m11*m.m20))*oneOverDeterminant;
		mInverse.m33 = (m.m00*(m.m11*m.m22 - m.m12*m.m21) + m.m01*(m.m12*m.m20 - m.m10*m.m22) + m.m02*(m.m10*m.m21 - m.m11*m.m20))*oneOverDeterminant;

		return Transpose<float, 4, 4>(mInverse);
	}

	// This is a left handed view matrix created from a camera position, up vector, and lookAt position
	inline Mat4x4 DirectXViewMatrix(Vec3& cameraPosition, Vec3& lookingDirection, Vec3& up)
	{
		Vec3 zAxis = Normalize(lookingDirection);
		Vec3 xAxis = Cross(up, zAxis);
		xAxis = Normalize(xAxis);
		Vec3 yAxis = Cross(zAxis, xAxis);
		
		return Mat4x4(xAxis.x, xAxis.y, xAxis.z, -Dot(cameraPosition, xAxis),
			          yAxis.x, yAxis.y, yAxis.z, -Dot(cameraPosition, yAxis),
					  zAxis.x, zAxis.y, zAxis.z, -Dot(cameraPosition, zAxis),
			          0,       0,       0,       1);
	}

	// This is a left handed orthographic projection row matrix which uses a view volume depth of 0 to 1
	inline Mat4x4 DirectXOrthoMatrix(float l, float r, float t, float b, float n, float f)
	{
		return Mat4x4(2 / r - l, 0,         0,         l + r / l - r,
			          0,         2 / t - b, 0,         t + b / b - t,
			          0,         0,         1 / f - n, n / n - f,
			          0,         0,         0,         1);
	}

	// This is a left handed orthographic proejction row matrix which uses a view volume depth of 0 to 1
	inline Mat4x4 DirectXOrthoMatrix(float width, float height, float n, float f)
	{
		return Mat4x4(2 / width, 0,          0,         0,
			          0,         2 / height, 0,         0,
					  0,         0,          1 / f - n, 0,
					  0,         0,          -n / f - n, 1);
	}

	// This is a left handed perspective projection row matrix which uses a frustrum depth of 0 to 1
	inline Mat4x4 DirectXPerspectiveMatrix(float fovY, float aspectRatio, float n, float f)
	{
		float zoomY = 1 / tan(fovY / 2);
		float zoomX = zoomY * aspectRatio;

		return Mat4x4(zoomX, 0,     0,         0,
			          0,     zoomY, 0,         0,
			          0,     0,     f / f - n, -n*f / f - n,
			          0,     0,     1,         0);
	}
	
}//end ZMath

#endif
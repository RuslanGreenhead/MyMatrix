//
// Matrix class implementation
//

#include "Matrix.h"
#pragma once

using namespace linalg;

template<typename T, typename Alloc> 
inline Matrix<T, Alloc>::Matrix(const size_t rows, const size_t columns, Alloc alloc)
	: m_alloc(alloc){
	T* ptr_temp = m_alloc.allocate(rows * columns);
	size_t i = 0;
	try{
		for (; i < rows * columns; ++i)
			m_alloc.construct(ptr_temp + i);
	}
	catch (...) {
		for (size_t j = 0; j != i; ++j)
			m_alloc.destroy(ptr_temp + j);
		m_alloc.deallocate(ptr_temp);
		throw;
	}
	m_ptr = ptr_temp;
	m_rows = rows;
	m_columns = columns;
	m_capacity = m_rows * m_columns;
}

template<typename T, typename Alloc>
template<typename Other>
inline Matrix<T, Alloc>::Matrix(std::initializer_list<Other> init_list, Alloc alloc)
	: m_alloc(alloc){
	typedef typename std::initializer_list<Other>::const_iterator const_iter;
	T* ptr_temp = m_alloc.allocate(init_list.size());
	size_t i = 0;
	try {
		for (const_iter c_it = std::cbegin(init_list); c_it != std::cend(init_list); ++c_it) {
			m_alloc.construct(ptr_temp + i, *c_it);
			++i;
		}
	}
	catch (...){
		for (size_t j = 0; j != i; ++j)
			m_alloc.destroy(ptr_temp + j);
		m_alloc.deallocate(ptr_temp);
		throw;
	}
	m_ptr = ptr_temp;
	m_rows = init_list.size();
	m_columns = 1;
	m_capacity = m_rows * m_columns;
}

template<typename T, typename Alloc>
template<typename Other>
inline Matrix<T, Alloc>::Matrix(std::initializer_list<std::initializer_list<Other>> list_list, Alloc alloc)
	: m_alloc(alloc){
	typedef typename std::initializer_list<Other>::const_iterator const_iter;
	typedef typename std::initializer_list<std::initializer_list<Other>>::const_iterator const_iter_global;
	const size_t rows = list_list.size();
	const size_t columns = list_list.begin()->size();
	for (const_iter_global c_it_gl = std::cbegin(list_list); c_it_gl != std::cend(list_list); ++c_it_gl) {
		if (c_it_gl->size() != columns) throw std::runtime_error("Error: different size of columns in different rows!");
	}
	T* ptr_temp = m_alloc.allocate(rows * columns);
	size_t i = 0;
	try{
		for (const_iter_global c_it_gl = std::cbegin(list_list); c_it_gl != std::cend(list_list); ++c_it_gl) {
			for (const_iter c_it = c_it_gl->begin(); c_it != c_it_gl->end(); ++c_it) {
				m_alloc.construct(ptr_temp + i, *c_it);
				++i;
			}
		}
	}
	catch (...){
		for (size_t j = 0; j != i; ++j)
			m_alloc.destroy(ptr_temp + j);
		m_alloc.deallocate(ptr_temp);
		throw;
	}
	m_ptr = ptr_temp;
	m_rows = rows;
	m_columns = columns;
	m_capacity = m_rows * m_columns;
}

template<typename T, typename Alloc>
inline Matrix<T, Alloc>::Matrix(const Matrix& object)
	: m_alloc(object.m_alloc)
{
	const size_t rows = object.get_rows();
	const size_t columns = object.get_columns();
	T* ptr_temp = m_alloc.allocate(rows * columns);
	size_t i = 0;
	try {
		for (size_t row = 0; row < rows; ++row) {
			for (size_t column = 0; column < columns; ++column) {
				m_alloc.construct(ptr_temp + i, object(row, column));
				++i;
			}
		}
	}
	catch (...){
		for (size_t j = 0; j != i; ++j)
			m_alloc.destroy(ptr_temp + j);
		m_alloc.deallocate(ptr_temp);
		throw;
	}
	m_ptr = ptr_temp;
	m_rows = rows;
	m_columns = columns;
	m_capacity = m_rows * m_columns;
}

template<typename T, typename Alloc>
template<typename Other, typename Alloc_Other>
inline Matrix<T, Alloc>::Matrix(const Matrix<Other, Alloc_Other>& object) {
	const size_t rows = object.get_rows();
	const size_t columns = object.get_columns();

	T* ptr_temp = m_alloc.allocate(rows * columns);

	size_t i = 0;
	try {
		for (size_t row = 0; row < rows; ++row) {
			for (size_t column = 0; column < columns; ++column) {
				m_alloc.construct(ptr_temp + i, static_cast<T>(object(row, column)));
				++i;
			}
		}
	}
	catch (...) {
		for (size_t j = 0; j != i; ++j)
			m_alloc.destroy(ptr_temp + j);
		m_alloc.deallocate(ptr_temp);
		throw;
	}
	m_ptr = ptr_temp;
	m_rows = rows;
	m_columns = columns;
	m_capacity = m_rows * m_columns;
}

template<typename T, typename Alloc>
inline Matrix<T, Alloc>::Matrix(Matrix&& object) noexcept {
	std::swap(m_ptr, object.m_ptr);
	std::swap(m_columns, object.m_columns);
	std::swap(m_rows, object.m_rows);
	std::swap(m_capacity, object.m_capacity);
	std::swap(m_alloc, object.m_alloc);
}

template<typename T, typename Alloc>
inline Matrix<T, Alloc>::~Matrix()noexcept {
	for (size_t i = 0; i < m_rows * m_columns; ++i)
		m_alloc.destroy(m_ptr + i);
	m_alloc.deallocate(m_ptr);
}

template<typename T, typename Alloc>
inline Matrix<T, Alloc>& linalg::Matrix<T, Alloc>::operator = (const Matrix& object) {
	if (m_ptr == object.m_ptr) return *this;
    if (object.size() > m_capacity) {  // We have to allocate new memory
        *this = Matrix(object); // Copy object to temporary -> MOVING it to *this
    }
    else {  // We have enough memory
        size_t i = 0;
        if (size() <= object.size()) {
            for (; i < size(); ++i)
                m_ptr[i] = static_cast<T>(object.m_ptr[i]);
            try {
                for (; i < object.size(); ++i)
                    m_alloc.construct(m_ptr + i, static_cast<T>(object.m_ptr[i]));
            }
            catch (...){
                for (size_t j = size(); j != i; ++j)
                    m_alloc.destroy(m_ptr + j);
                throw;
            }
        }
        else {
            for (; i < object.size(); ++i)
                m_ptr[i] = static_cast<T>(object.m_ptr[i]);
            for (; i < size(); ++i)
                m_alloc.destroy(m_ptr + i);
        }
        m_rows = object.get_rows();
        m_columns = object.get_columns();
    }
    return *this;
}

template<typename T, typename Alloc>
template<typename Other, typename Alloc_Other>
inline Matrix<T, Alloc>& linalg::Matrix<T, Alloc>::operator = (const Matrix<Other, Alloc_Other>& object) {
	if (object.size() > m_capacity) {
		*this = Matrix(object);
	}
	else {
		size_t i = 0;
		if (size() <= object.size()){
			for (; i < size(); ++i)
				m_ptr[i] = static_cast<T>(object.m_ptr[i]);
			try {
				for (; i < object.size(); ++i)
					m_alloc.construct(m_ptr + i, static_cast<T>(object.m_ptr[i]));
			}
			catch (...){
				for (size_t j = size(); j != i; ++j)
					m_alloc.destroy(m_ptr + j);
				throw;
			}
		}else{
			for (; i < object.size(); ++i) m_ptr[i] = static_cast<T>(object.m_ptr[i]);
			for (; i < size(); ++i) m_alloc.destroy(m_ptr + i);
		}
		m_rows = object.get_rows();
		m_columns = object.get_columns();
	}
	return *this;
}

template<typename T, typename Alloc>
inline Matrix<T, Alloc>& linalg::Matrix<T, Alloc>::operator = (Matrix&& object) noexcept {
	std::swap(m_ptr, object.m_ptr);
	std::swap(m_columns, object.m_columns);
	std::swap(m_rows, object.m_rows);
	std::swap(m_capacity, object.m_capacity);
	std::swap(m_alloc, object.m_alloc);
	return *this;
}

template<typename T, typename Alloc>
template<typename Other, typename Alloc_Other>
inline Matrix<T, Alloc>& Matrix<T, Alloc>::operator += (const Matrix<Other, Alloc_Other>& object) {
	if (m_rows != object.m_rows || m_columns != object.m_columns)
		throw std::runtime_error("Error: different shapes for operator +=!");
	for (size_t row = 0; row < object.m_rows; ++row) {
		for (size_t col = 0; col < object.m_columns; ++col) {
			this->operator()(row, col) += static_cast<T>(object(row, col));
		}
	}
	return *this;
}

template<typename T, typename Alloc>
template<typename Other, typename Alloc_Other>
inline Matrix<T, Alloc>& Matrix<T, Alloc>::operator -= (const Matrix<Other, Alloc_Other>& object) {
	if (m_rows != object.m_rows || m_columns != object.m_columns)
		throw std::runtime_error("Error: different shapes for operator -=!");
	for (size_t row = 0; row < object.m_rows; ++row) {
		for (size_t col = 0; col < object.m_columns; ++col) {
			this->operator()(row, col) -= static_cast<T>(object(row, col));
		}
	}
	return *this;
}

template<typename T, typename Alloc>
template<typename Other>
inline Matrix<T, Alloc>& Matrix<T, Alloc>::operator *= (const Other& value) {
	for (size_t col = 0; col < m_columns; ++col) {
		for (size_t row = 0; row < m_rows; ++row) {
			this->operator()(row, col) *= static_cast<T>(value);
		}
	}
	return *this;
}

template<typename T, typename Alloc>
template<typename Other, typename Alloc_Other>
inline Matrix<T, Alloc>& Matrix<T, Alloc>::operator *= (const Matrix<Other, Alloc_Other>& object) {
	if (m_columns != object.m_rows)
		throw std::runtime_error("Error: bad shapes for operator *=!");
	Matrix obj_new(m_rows, object.m_columns);
	for (size_t col = 0; col < object.m_columns; ++col) {
		for (size_t row = 0; row < m_rows; ++row) {
			for (size_t term = 0; term < m_columns; ++term) {
				obj_new(row, col) += this->operator()(row, term) * object(term, col);
			}
		}
	}
	*this = std::move(obj_new);
	return *this;
}

template<typename T, typename Alloc>
inline T& Matrix<T, Alloc>::operator() (size_t row, size_t column) {
	if (!m_ptr) throw std::runtime_error("Error: operator () asked for element of empty matrix!");
	if (m_rows <= row) throw std::runtime_error("Error: operator () asked for element: bad row!");
	if (m_columns <= column) throw std::runtime_error("Error: operator () asked for element: bad column!");
	return m_ptr[row * m_columns + column];
}

template<typename T, typename Alloc>
inline const T& Matrix<T, Alloc>::operator() (size_t row, size_t column) const {
	if (!m_ptr) throw std::runtime_error("Error: operator () asked for element of empty matrix!");
	if (m_rows <= row) throw std::runtime_error("Error: operator () asked for element: bad row!");
	if (m_columns <= column) throw std::runtime_error("Error: operator () asked for element: bad column!");
	return m_ptr[row * m_columns + column];
}
#include "Matrix.h"
#pragma once

using namespace linalg;

// Конструктор с 2 параметрами
template<typename T, typename Alloc> 
inline Matrix<T, Alloc>::Matrix(const size_t rows, const size_t columns, Alloc alloc)
	: m_alloc(alloc)
{
	T* ptr_temp = m_alloc.allocate(rows * columns); // Просто выделили память
	size_t i = 0; // глобальный индекс (чтобы вне try использовать)
	try { // с помощью него буду отслеживать на каком я конструкторе
		for (; i < rows * columns; ++i) // размещающий new
			m_alloc.construct(ptr_temp + i); // запускает дефолтный конструктор
	}
	catch (...) { // в каком-то из конструкторов выбросилось исключение?!
		for (size_t j = 0; j != i; ++j) // пройдёмся по всем уже созданным объектам
			m_alloc.destroy(ptr_temp + j); // и запустим у них деструкторы
		m_alloc.deallocate(ptr_temp); // освободим память
		throw; // прокинем исключение дальше
	}
	// теперь память успешно выделена, можно её сохранить и поменять размер
	m_ptr = ptr_temp;
	m_rows = rows;
	m_columns = columns;
	m_capacity = m_rows * m_columns;
}

// Инициализировать вектор (вертикальный столбец)
template<typename T, typename Alloc>
template<typename Other>
inline Matrix<T, Alloc>::Matrix(std::initializer_list<Other> init_list, Alloc alloc)
	: m_alloc(alloc)
{
	typedef typename std::initializer_list<Other>::const_iterator const_iter;
	T* ptr_temp = m_alloc.allocate(init_list.size()); // Просто выделили память
	size_t i = 0; // глобальный индекс (чтобы вне try использовать) 
	try { // с помощью него буду отслеживать на каком я конструкторе
		for (const_iter c_it = std::cbegin(init_list); c_it != std::cend(init_list); ++c_it) {
			m_alloc.construct(ptr_temp + i, *c_it); // запускает конструктор с параметрами
			++i;
		}
	}
	catch (...) { // в каком-то из конструкторов выбросилось исключение?!
		for (size_t j = 0; j != i; ++j) // пройдёмся по всем уже созданным объектам
			m_alloc.destroy(ptr_temp + j); // и запустим у них деструкторы
		m_alloc.deallocate(ptr_temp); // освободим память
		throw; // прокинем исключение дальше
	}
	// теперь память успешно выделена, можно её сохранить и поменять размер
	m_ptr = ptr_temp;
	m_rows = init_list.size();
	m_columns = 1;
	m_capacity = m_rows * m_columns;
}

// Инициализировать матрицу initializer_list сосотящий из initializer_list
template<typename T, typename Alloc>
template<typename Other>
inline Matrix<T, Alloc>::Matrix(std::initializer_list<std::initializer_list<Other>> list_list, Alloc alloc)
	: m_alloc(alloc)
{
	typedef typename std::initializer_list<Other>::const_iterator const_iter;
	typedef typename std::initializer_list<std::initializer_list<Other>>::const_iterator const_iter_global;
	const size_t rows = list_list.size();
	const size_t columns = list_list.begin()->size();
	for (const_iter_global c_it_gl = std::cbegin(list_list); c_it_gl != std::cend(list_list); ++c_it_gl) {
		if (c_it_gl->size() != columns) throw std::runtime_error("Error: different size of columns in different rows!");
	}
	T* ptr_temp = m_alloc.allocate(rows * columns); // Просто выделили память
	size_t i = 0; // глобальный индекс (чтобы вне try использовать) 
	try { // с помощью него буду отслеживать на каком я конструкторе
		for (const_iter_global c_it_gl = std::cbegin(list_list); c_it_gl != std::cend(list_list); ++c_it_gl) {
			for (const_iter c_it = c_it_gl->begin(); c_it != c_it_gl->end(); ++c_it) {
				m_alloc.construct(ptr_temp + i, *c_it); // запускает конструктор с параметрами
				++i;
			}
		}
	}
	catch (...) { // в каком-то из конструкторов выбросилось исключение?!
		for (size_t j = 0; j != i; ++j) // пройдёмся по всем уже созданным объектам
			m_alloc.destroy(ptr_temp + j); // и запустим у них деструкторы
		m_alloc.deallocate(ptr_temp); // освободим память
		throw; // прокинем исключение дальше
	}
	// теперь память успешно выделена, можно её сохранить и поменять размер
	m_ptr = ptr_temp;
	m_rows = rows;
	m_columns = columns;
	m_capacity = m_rows * m_columns;
}

// Конструктор копирования
template<typename T, typename Alloc>
inline Matrix<T, Alloc>::Matrix(const Matrix& object)
	: m_alloc(object.m_alloc)
{
	const size_t rows = object.get_rows();
	const size_t columns = object.get_columns();
	T* ptr_temp = m_alloc.allocate(rows * columns); // Просто выделили память
	size_t i = 0; // глобальный индекс (чтобы вне try использовать) 
	try { // с помощью него буду отслеживать на каком я конструкторе
		for (size_t row = 0; row < rows; ++row) {
			for (size_t column = 0; column < columns; ++column) { // размещающий new
				m_alloc.construct(ptr_temp + i, object(row, column)); // запускает конструктор с параметрами
				++i;
			}
		}
	}
	catch (...) { // в каком-то из конструкторов выбросилось исключение?!
		for (size_t j = 0; j != i; ++j) // пройдёмся по всем уже созданным объектам
			m_alloc.destroy(ptr_temp + j); // и запустим у них деструкторы
		m_alloc.deallocate(ptr_temp); // освободим память
		throw; // прокинем исключение дальше
	}
	// теперь память успешно выделена, можно её сохранить и поменять размер
	m_ptr = ptr_temp;
	m_rows = rows;
	m_columns = columns;
	m_capacity = m_rows * m_columns;
}

// Конструктор копирования от матрицы другого типа
template<typename T, typename Alloc>
template<typename Other, typename Alloc_Other>
inline Matrix<T, Alloc>::Matrix(const Matrix<Other, Alloc_Other>& object) {
	const size_t rows = object.get_rows();
	const size_t columns = object.get_columns();

	T* ptr_temp = m_alloc.allocate(rows * columns); // Просто выделили память


	size_t i = 0; // глобальный индекс (чтобы вне try использовать)
	try { // с помощью него буду отслеживать на каком я конструкторе
		for (size_t row = 0; row < rows; ++row) {
			for (size_t column = 0; column < columns; ++column) { // размещающий new
				m_alloc.construct(ptr_temp + i, static_cast<T>(object(row, column))); // запускает конструктор с параметрами
				++i;
			}
		}
	}
	catch (...) { // в каком-то из конструкторов выбросилось исключение?!
		for (size_t j = 0; j != i; ++j) // пройдёмся по всем уже созданным объектам
			m_alloc.destroy(ptr_temp + j); // и запустим у них деструкторы
		m_alloc.deallocate(ptr_temp); // освободим память
		throw; // прокинем исключение дальше
	}
	// теперь память успешно выделена, можно её сохранить и поменять размер
	m_ptr = ptr_temp;
	m_rows = rows;
	m_columns = columns;
	m_capacity = m_rows * m_columns;
}

// Перемещающий конструктор
template<typename T, typename Alloc>
inline Matrix<T, Alloc>::Matrix(Matrix&& object) noexcept {// исключения точно не вылетят (тут неоткуда)
	std::swap(m_ptr, object.m_ptr);
	std::swap(m_columns, object.m_columns);
	std::swap(m_rows, object.m_rows);
	std::swap(m_capacity, object.m_capacity);
	std::swap(m_alloc, object.m_alloc);
} // теперь во временном объекте наши старые ресурсы => они умрут снаружи

// Деструктор
template<typename T, typename Alloc>
inline Matrix<T, Alloc>::~Matrix()noexcept {
	for (size_t i = 0; i < m_rows * m_columns; ++i)// пройдёмся по всем своим объектам
		m_alloc.destroy(m_ptr + i); // и запустим у них деструкторы
	m_alloc.deallocate(m_ptr); // освободим память
}

// Оператор присваивания копирующий
template<typename T, typename Alloc>
inline Matrix<T, Alloc>& linalg::Matrix<T, Alloc>::operator = (const Matrix& object) {
	if (m_ptr == object.m_ptr) return *this; // Проверка на самоприсваивание
    if (object.size() > m_capacity) { // придётся перевыделять память
        *this = Matrix(object); // скопировали объект во временный и своровали у него ресурсы с помощью перемещения
        // теперь старые ресурсы нашего класса у временного и они подчистятся, когда закончится инструкция (т.е. уже тут)
    }
    else { // иначе: вместимости моей матрицы хватит на актуальный размер объекта
        size_t i = 0; // с помощью этого индекса пройдёмся по всем элементам
        if (size() <= object.size()) { // т.е. актуальный размер имеющейся матрицы увеличится или не изменится
            for (; i < size(); ++i)
                m_ptr[i] = static_cast<T>(object.m_ptr[i]); // присваивание может выкинуть исключение, но это не нарушит целостность объекта
            try { // нужно проконтролировать работу конструкторов у новых объектов
                for (; i < object.size(); ++i)
                    m_alloc.construct(m_ptr + i, static_cast<T>(object.m_ptr[i]));
            }
            catch (...) { // если при создании новых объектов вылетело исключение, то эти новые надо разрушить
                for (size_t j = size(); j != i; ++j)
                    m_alloc.destroy(m_ptr + j); // запуск деструкторов
                throw;
            }
        }
        else { // т.е. актуальный размер имеющейся матрицы уменьшится
            for (; i < object.size(); ++i)
                m_ptr[i] = static_cast<T>(object.m_ptr[i]);
            for (; i < size(); ++i) // не нужно контролировать работу деструкторов т.к. они не должны выкидывать исключения
                m_alloc.destroy(m_ptr + i); // разрушим не нужные нам элементы
        }
        // актуальные размеры матрицы изменились:
        m_rows = object.get_rows();
        m_columns = object.get_columns();
        // НО capactiy не изменилось т.к. память не перевыделяли
    }
    return *this;
}

// Оператор присваивания копирующий от матрицы другого типа
template<typename T, typename Alloc>
template<typename Other, typename Alloc_Other>
inline Matrix<T, Alloc>& linalg::Matrix<T, Alloc>::operator = (const Matrix<Other, Alloc_Other>& object) {
	// Нет смысла делать проверку на самоприсваивание т.к. там матрица другого типа => она точно другая
	if (object.size() > m_capacity) { // придётся перевыделять память
		*this = Matrix(object); // скопировали объект во временный и своровали у него ресурсы с помощью перемещения
		// теперь старые ресурсы нашего класса у временного и они подчистятся, когда закончится инструкция (т.е. уже тут)
	}
	else { // иначе: вместимости моей матрицы хватит на актуальный размер объекта
		size_t i = 0; // с помощью этого индекса пройдёмся по всем элементам
		if (size() <= object.size()) { // т.е. актуальный размер имеющейся матрицы увеличится или не изменится
			for (; i < size(); ++i)
				m_ptr[i] = static_cast<T>(object.m_ptr[i]); // присваивание может выкинуть исключение, но это не нарушит целостность объекта
			try { // нужно проконтролировать работу конструкторов у новых объектов
				for (; i < object.size(); ++i)
					m_alloc.construct(m_ptr + i, static_cast<T>(object.m_ptr[i]));
			}
			catch (...) { // если при создании новых объектов вылетело исключение, то эти новые надо разрушить
				for (size_t j = size(); j != i; ++j)
					m_alloc.destroy(m_ptr + j); // запуск деструкторов
				throw;
			}
		}
		else { // т.е. актуальный размер имеющейся матрицы уменьшится
			for (; i < object.size(); ++i)
				m_ptr[i] = static_cast<T>(object.m_ptr[i]);
			for (; i < size(); ++i) // не нужно контролировать работу деструкторов т.к. они не должны выкидывать исключения
				m_alloc.destroy(m_ptr + i); // разрушим не нужные нам элементы
		}
		// актуальные размеры матрицы изменились:
		m_rows = object.get_rows();
		m_columns = object.get_columns();
		// НО capactiy не изменилось т.к. память не перевыделяли
	}
	return *this;
}

// Оператор присваивания перемещающий 
template<typename T, typename Alloc>
inline Matrix<T, Alloc>& linalg::Matrix<T, Alloc>::operator = (Matrix&& object) noexcept {
	std::swap(m_ptr, object.m_ptr);
	std::swap(m_columns, object.m_columns);
	std::swap(m_rows, object.m_rows);
	std::swap(m_capacity, object.m_capacity);
	std::swap(m_alloc, object.m_alloc);
	return *this;
} // теперь во временном объекте наши старые ресурсы => они умрут снаружи

// Оператор присваивающего суммирования c матрицей другого типа
template<typename T, typename Alloc>
template<typename Other, typename Alloc_Other>
inline Matrix<T, Alloc>& Matrix<T, Alloc>::operator += (const Matrix<Other, Alloc_Other>& object) {
	if (m_rows != object.m_rows || m_columns != object.m_columns)
		throw std::runtime_error("Error: different shapes for operator +=!");
	for (size_t row = 0; row < object.m_rows; ++row) {
		for (size_t col = 0; col < object.m_columns; ++col) {
			this->operator()(row, col) += static_cast<T>(object(row, col));// Оператор += между типами Т и Other => может выкинуть исключение
		} // но это не нарушит целостность объекта (размер задан, значения заполнены)
	}
	return *this;
}


// Оператор присваивающего вычитания c матрицей другого типа
template<typename T, typename Alloc>
template<typename Other, typename Alloc_Other>
inline Matrix<T, Alloc>& Matrix<T, Alloc>::operator -= (const Matrix<Other, Alloc_Other>& object) {
	if (m_rows != object.m_rows || m_columns != object.m_columns)
		throw std::runtime_error("Error: different shapes for operator -=!");
	for (size_t row = 0; row < object.m_rows; ++row) {
		for (size_t col = 0; col < object.m_columns; ++col) {
			this->operator()(row, col) -= static_cast<T>(object(row, col)); // Оператор -= между типами Т и Other => может выкинуть исключение
		} // но это не нарушит целостность объекта (размер задан, значения заполнены)
	}
	return *this;
}


// Оператор присваивающего умножения на число другого типа
template<typename T, typename Alloc>
template<typename Other>
inline Matrix<T, Alloc>& Matrix<T, Alloc>::operator *= (const Other& value) {
	for (size_t col = 0; col < m_columns; ++col) {
		for (size_t row = 0; row < m_rows; ++row) {
			this->operator()(row, col) *= static_cast<T>(value); // Оператор *= между типами Т и Other => может выкинуть исключение
		} // но это не нарушит целостность объекта (размер задан, значения заполнены)
	}
	return *this;
}

// Оператор присваивающего умножения на матрицу другого типа
template<typename T, typename Alloc>
template<typename Other, typename Alloc_Other>
inline Matrix<T, Alloc>& Matrix<T, Alloc>::operator *= (const Matrix<Other, Alloc_Other>& object) {
	if (m_columns != object.m_rows)
		throw std::runtime_error("Error: bad shapes for operator *=!");
	Matrix obj_new(m_rows, object.m_columns); // пустая матрица, т.е. элементы которой построены с помощью дефолтных конструкторов
	for (size_t col = 0; col < object.m_columns; ++col) {
		for (size_t row = 0; row < m_rows; ++row) {
			for (size_t term = 0; term < m_columns; ++term) {
				obj_new(row, col) += this->operator()(row, term) * object(term, col);
			}
		}
	}
	*this = std::move(obj_new); // теперь в obj_new наши старые ресурсы, которые "умрут" при выходе из тела оператора
	return *this;
}

// оператор вызова функции (принимает два аргумента будто [i][j])
template<typename T, typename Alloc>
inline T& Matrix<T, Alloc>::operator() (size_t row, size_t column) {
	if (!m_ptr) throw std::runtime_error("Error: operator () asked for element of empty matrix!");
	if (m_rows <= row) throw std::runtime_error("Error: operator () asked for element: bad row!");
	if (m_columns <= column) throw std::runtime_error("Error: operator () asked for element: bad column!");
	return m_ptr[row * m_columns + column];
}

// оператор вызова функции для константной матрицы
template<typename T, typename Alloc>
inline const T& Matrix<T, Alloc>::operator() (size_t row, size_t column) const {
	if (!m_ptr) throw std::runtime_error("Error: operator () asked for element of empty matrix!");
	if (m_rows <= row) throw std::runtime_error("Error: operator () asked for element: bad row!");
	if (m_columns <= column) throw std::runtime_error("Error: operator () asked for element: bad column!");
	return m_ptr[row * m_columns + column];
}
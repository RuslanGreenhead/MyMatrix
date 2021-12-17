

#ifndef LAB_2_LINALGERROR_H
#define LAB_2_LINALGERROR_H

#endif //LAB_2_LINALGERROR_H
#pragma once
using std::exception;

namespace linalg {
    class LinAlgError : public std::runtime_error {//расширяем функционал родителя
    public:
        LinAlgError(const char *ch_arr, int state) : std::runtime_error(ch_arr),
                                                     m_state(state) {}//базовый конструктор с названием ошибки
        int get_state() const { return m_state; }

    private:
        int m_state;
    };
}
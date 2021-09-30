#pragma once

template<class T>
class Observer {
  public:
    Observer() = default;
    virtual ~Observer() = default;
    Observer(const Observer &) = default;
    Observer(Observer &&) noexcept = default;
    auto operator=(const Observer &) -> Observer & = default;
    auto operator=(Observer &&) noexcept -> Observer & = default;
    virtual void update(T *s) = 0;
};
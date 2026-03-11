#pragma once
#include <exception>
#include <string>

class Exception : public std::exception {
private:
	std::string _msg;
public:
	explicit Exception(std::string msg) : _msg(std::move(msg)) {}

	/*const std::string& getMsg() const {
		return _msg;
	}*/
	Exception(const Exception& other) noexcept = default;
	Exception& operator=(const Exception& other) noexcept = default;
	Exception(Exception&& other) noexcept = default;
	Exception& operator=(Exception&& other) noexcept = default;
	~Exception() override = default;

	const char* what() const noexcept override {
		return _msg.c_str();
	}
};
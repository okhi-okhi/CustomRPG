#pragma once
#include <iostream>
#include <exception>
#include "../I18n/I18n.h"

using std::string;

class InvalidFileException final : public std::exception{
private:
    string file;

public:
    explicit InvalidFileException(string file) : file(std::move(file))
    {
	    std::cout << what() << std::endl;
	    exit(1);
    }

    string what() {
        return I18n::instance().get("system.exception.invalidFile", { {"file", file} });
    }
};

class BadValueException final : public std::exception {
private:
    string file;
    string error;

public:
    explicit BadValueException(string file, string error) :file(std::move(file)), error(std::move(error))
    {
        std::cout << what() << std::endl;
        std::cout << this->error << std::endl;
        exit(2);
    }

    string what() {
        return I18n::instance().get("system.exception.badValueFunction", { {"file", file} });
    }
};

class OutOfRangeException final : public std::exception {
private:
    int index;
    int max;

public:
    explicit OutOfRangeException(const int index, const int max) : index(index), max(max)
    {
        std::cout << what() << std::endl;
        exit(3);
    }

    string what() {
        return I18n::instance().get("system.exception.outOfRange",
            { {"index", std::to_string(index)},
			  {"max", std::to_string(max - 1)} });
    }
};

class InvBadAmountException final : public std::exception {
private:
    int amount;

public:
    explicit InvBadAmountException(const int amount) : amount(amount)
    {
        std::cout << what() << std::endl;
        exit(4);
    }

    string what() {
        using std::to_string;
        return I18n::instance().get("system.exception.invBadAmount", { {"amount", to_string(amount)} });
    }
};

class BadChanceException final : public std::exception {
private:
    int totalChance;

public:
    explicit BadChanceException(const int totalChance) : totalChance(totalChance)
    {
        std::cout << what() << std::endl;
        exit(5);
    }

    string what() {
        using std::to_string;
        return I18n::instance().get("system.exception.badChance", { {"totalChance", to_string(totalChance)} });
    }
};

class NoReadFunctionException final : public std::exception {
private:
    string json;

public:
    explicit NoReadFunctionException(string j) : json(std::move(j))
    {
        std::cout << what() << std::endl;
        exit(6);
    }

    string what() {
        return I18n::instance().get("system.exception.noReadFunction", { {"json", json} });
    }
};

class BadStringException final : public std::exception {
private:
    string json;

public:
    explicit BadStringException(string j) : json(std::move(j))
    {
        std::cout << what() << std::endl;
        exit(7);
    }

    string what() {
        return I18n::instance().get("system.exception.badString", { {"json", json} });
    }
};

class InvalidKeyException final : public std::exception {
private:
    string key;

public:
    explicit InvalidKeyException(string key) : key(std::move(key))
    {
        std::cout << what() << std::endl;
        exit(8);
    }

    string what() {
        return I18n::instance().get("system.exception.invalidKey", { {"key", key} });
    }
};
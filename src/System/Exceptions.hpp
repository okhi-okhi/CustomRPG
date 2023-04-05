#pragma once
#include <iostream>
#include <exception>

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
        return "Can't find file! file: " + this->file;
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
        return "Conversion failed while reading file! file: " + this->file;
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
        return "Index less than 0 or out of range! index: "
    		+ std::to_string(this->index) + ", limit: " + std::to_string(this->max-1);
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
        return "Amount provided when removing item is less than 1! amount: " + std::to_string(this->amount);
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
        return "If chanceTable contains '-1', the total chance cannot exceed 1! total chance: " + std::to_string(this->totalChance);
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
        return "Can't read json! json: " + this->json;
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
        return "Can't convert json to value! json: " + this->json;
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
        return "Can't find key! key:" + this->key;
    }
};
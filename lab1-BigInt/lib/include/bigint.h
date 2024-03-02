#pragma once

class BigInt {
private:
	std::string bigint;
	char sgn = '+';
	BigInt(std::string new_bigint, char s);
	std::string bin() const;
	BigInt dec(std::string& str_bit) const;
public:
	BigInt();
	BigInt(int new_bigint);
	BigInt(std::string new_bigint);
	BigInt(const BigInt& new_bigint);
	~BigInt() = default;
	BigInt& operator=(const BigInt& new_bigint);
	BigInt operator~() const;
	BigInt& operator++();
	const BigInt operator++(int);
	BigInt& operator--();
	const BigInt operator--(int);
	BigInt& operator+=(const BigInt& n2);
	BigInt& operator*=(const BigInt& n2);
	BigInt& operator-=(const BigInt& n2);
	BigInt& operator/=(const BigInt& n2);
	BigInt& operator^=(const BigInt& n2);
	BigInt& operator%=(const BigInt& n2);
	BigInt& operator&=(const BigInt& n2);
	BigInt& operator|=(const BigInt& n2);
	BigInt operator+() const;
	BigInt operator-() const;
	bool operator==(const BigInt& n2) const;
	bool operator!=(const BigInt& n2) const;
	bool operator<(const BigInt& n2) const;
	bool operator>(const BigInt& n2) const;
	bool operator<=(const BigInt& n2) const;
	bool operator>=(const BigInt& n2) const;
	operator int() const;
	operator std::string() const;
	size_t size() const;
	BigInt absb() const;
};

BigInt operator+(const BigInt& n1, const BigInt& n2);
BigInt operator-(const BigInt& n1, const BigInt& n2);
BigInt operator*(const BigInt& n1, const BigInt& n2);
BigInt operator/(const BigInt& n1, const BigInt& n2);
BigInt operator^(const BigInt& n1, const BigInt& n2);
BigInt operator%(const BigInt& n1, const BigInt& n2);
BigInt operator&(const BigInt& n1, const BigInt& n2);
BigInt operator|(const BigInt& n1, const BigInt& n2);
std::ostream& operator<<(std::ostream& o, const BigInt& i);

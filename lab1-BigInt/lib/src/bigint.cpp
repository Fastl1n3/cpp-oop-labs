#include <string>
#include <iostream>
#include <algorithm>
#include <climits>
#include "../include/bigint.h"

BigInt::BigInt() {
	bigint = "0";
}

BigInt::BigInt(int new_bigint) {
	if (new_bigint < 0) {
		sgn = '-';
	}
	if (new_bigint == 0) {
		bigint.push_back('0');
	}
	while (new_bigint != 0) {
		bigint.push_back(abs(new_bigint % 10) + '0');
		new_bigint /= 10;
	}
}

BigInt::BigInt(std::string new_bigint) {  // бросать исключение std::invalid_argument при ошибке
	size_t len = new_bigint.length();
	if (len == 0) {
		throw std::invalid_argument("Ivalid syntax");
	}
	if (new_bigint[0] == '+' || new_bigint[0] == '-') {
		sgn = new_bigint[0];
		new_bigint.erase(0, 1);
		if (len == 1) {
			throw std::invalid_argument("Ivalid syntax");
		}
		len--;
	}
	int flag = 1;
	for (int i = 0; i < len; i++) {
		if (new_bigint[i] > '9' || new_bigint[i] < '0') {
			throw std::invalid_argument("Ivalid syntax");
		}
		if (i == 0 && new_bigint[i] == '0') {
			flag = 0;
		}
		if (flag == 0 && new_bigint[i] == '0' && len > 1) {
			std::cout << new_bigint << " : " << len << std::endl;
			new_bigint.erase(i, 1);
			len--;
			i--;
			if (i == len - 2 || new_bigint[i + 1] != '0') {
				flag = 1;
			}
		}
	}
	bigint = new_bigint;
	if (bigint == "0") {
		sgn = '+';
	}
	std::reverse(bigint.begin(), bigint.end());
}

BigInt::BigInt(std::string new_bigint, char s) {
	bigint = new_bigint;
	sgn = s;
}

BigInt::BigInt(const BigInt& new_bigint) {
	bigint = new_bigint.bigint;
	sgn = new_bigint.sgn;
}

BigInt& BigInt::operator=(const BigInt& new_bigint) {
	bigint = new_bigint.bigint;
	sgn = new_bigint.sgn;
	return *this;
}

std::string BigInt::bin() const {
	BigInt a1 = *this;
	std::string a1_bit_str;
	while (a1 != BigInt(0)) {
		std::string a1_str = a1.bigint;
		a1_bit_str.push_back(a1_str[0] % 2 + '0');
		a1 /= 2;
	}
	a1_bit_str.push_back('0');
	if (sgn == '-') {
		size_t len_bit = a1_bit_str.length();
		int rank = 0;
		for (int i = 0; i < len_bit - 1; i++) {
			a1_bit_str[i] = !(a1_bit_str[i] - '0') + '0';
			if (rank != 0) {
				if (a1_bit_str[i] == '0') {
					a1_bit_str[i] = '1';
					rank = 0;
				}
				else {
					a1_bit_str[i] = '0';
					rank = 1;
				}
			}
			if (i == 0) {
				if (a1_bit_str[i] == '0') {
					a1_bit_str[i] = '1';
				}
				else {
					a1_bit_str[i] = '0';
					rank = 1;
				}
			}
		}
		a1_bit_str[len_bit - 1] = '1';
	}
	return a1_bit_str;
}

BigInt BigInt::dec(std::string& str_bit) const {
	int str_bit_len = str_bit.length();
	BigInt out(0);
	if (str_bit[str_bit_len - 1] == '0') {
		for (int i = str_bit_len - 2; i >= 0; i--) {
			out *= 2;
			out += (str_bit[i] - '0');
		}
	}
	else {
		int rank = 0;
		for (int i = 0; i < str_bit_len - 1; i++) {
			if (rank != 0) {
				if (str_bit[i] == '1') {
					str_bit[i] = '0';
					rank = 0;
				}
				else {
					str_bit[i] = '1';
					rank = 1;
				}
			}
			if (i == 0) {
				if (str_bit[i] == '1')
					str_bit[i] = '0';
				else {
					str_bit[i] = '1';
					rank = 1;
				}
			}
			str_bit[i] = !(str_bit[i] % 2) + '0';
		}
		for (int i = str_bit_len - 2; i >= 0; i--) {
			out *= 2;
			out += (str_bit[i] - '0');
		}
		out = -out;
	}
	return out;
}

BigInt BigInt::operator~() const {
	BigInt a1 = *this;
	std::string str_bit = a1.bin();
	int str_bit_len = str_bit.length();
	for (int i = 0; i < str_bit_len; i++) {
		str_bit[i] = str_bit[i] == '1' ? '0' : '1';
	}
	a1 = dec(str_bit);
	return a1;
}

BigInt& BigInt::operator++() {
	*this += 1;
	return *this;
}

const BigInt BigInt::operator++(int) {
	BigInt d = *this;
	++*this;
	return d;
}

BigInt& BigInt::operator--() {
	*this -= 1;
	return *this;
}

const BigInt BigInt::operator--(int) {
	BigInt d = *this;
	--*this;
	return d;
}

BigInt& BigInt::operator+=(const BigInt& n2) {
	char s = '+';
	std::string newbigint;
	if (sgn == '-' && n2.sgn == '-') {
		sgn = '-';
	}
	else {
		if (sgn == '-') {
			BigInt b = n2;
			b -= (-*this);
			*this = b;
			return *this;
		}
		if (n2.sgn == '-') {
			*this -= (-n2);
			return *this;
		}
	}
	size_t len1 = bigint.length();
	size_t len2 = n2.bigint.length();
	size_t len_max = std::max(len1, len2);
	size_t len_min = std::min(len1, len2);
	int i = 0;
	int rank = 0;
	for (i; i < len_min; i++) {
		char digit1 = bigint[i];
		char digit2 = n2.bigint[i];
		int res = digit1 - '0' + digit2 - '0' + rank;
		newbigint.push_back((res % 10) + '0');
		rank = res / 10;
	}
	for (i; i < len_max; i++) {
		int res;
		if (len1 > len2) {
			res = bigint[i] - '0' + rank;
		}
		else {
			res = n2.bigint[i] - '0' + rank;
		}
		rank = res / 10;
		newbigint.push_back((res % 10) + '0');
	}
	if (rank == 1) {
		newbigint.push_back(1 + '0');
	}
	bigint = newbigint;
	return *this;
}

BigInt& BigInt::operator*=(const BigInt& n2) {
	if (*this == BigInt(0)) {
		return *this;
	}
	if (n2 == BigInt(0)) {
		*this = 0;
		return *this;
	}
	size_t len1 = bigint.length();
	size_t len2 = n2.bigint.length();
	int flag = len1 > len2 ? 1 : 0;
	if (sgn == '-' && n2.sgn == '-' || sgn == '+' && n2.sgn == '+') {
		sgn = '+';
	}
	else {
		sgn = '-';
	}
	BigInt out(0);
	std::string nulls;
	for (int i = 0; i < (flag ? len2 : len1); i++) {
		std::string terms;
		terms = nulls + terms;
		int res, rank = 0;
		for (int j = 0; j < (!flag ? len2 : len1); j++) {
			if (flag) {
				res = (bigint[j] - '0') * (n2.bigint[i] - '0') + rank;
			}
			else {
				res = (n2.bigint[j] - '0') * (bigint[i] - '0') + rank;
			}
			rank = res / 10;
			terms.push_back((res % 10) + '0');
		}
		nulls += '0';
		if (rank != 0) {
			terms.push_back(rank + '0');
		}
		out += BigInt(terms, '+');
	}
	if (sgn == '-') {
		out = -out;
	}
	*this = out;
	return *this;
}

BigInt& BigInt::operator-=(const BigInt& n2) {
	if (sgn == '-' && n2.sgn == '+') {
		*this = -*this;
		*this += n2;
		*this = -*this;
		return *this;
	}
	if (sgn == '+' && n2.sgn == '-') {
		*this += (-n2);
		return *this;
	}
	if (sgn == '-' && n2.sgn == '-') {
		if (*this > n2) {
			BigInt b = -n2;
			b -= (-*this);
			*this = b;
			return *this;
		}
		else {
			sgn = '-';
		}
	}
	if (sgn == '+' && n2.sgn == '+') {
		if (*this < n2) {
			BigInt b = n2;
			b -= *this;
			*this = -b;
			return *this;
		}
	}
	std::string num1 = bigint;
	size_t len1 = bigint.length();
	size_t len2 = n2.bigint.length();
	size_t len_max = std::max(len1, len2);
	size_t len_min = std::min(len1, len2);
	int i = 0;
	std::string newbigint;
	int rank = 0;
	for (i; i < len_min; i++) {
		char digit1 = num1[i];
		char digit2 = n2.bigint[i];
		int res;
		if (digit1 < digit2) {
			res = 10 + digit1 - digit2;
			int j = i + 1;
			while (num1[j] == '0') {
				num1[j] = '9';
				j++;
			}
			num1[j]--;
		}
		else {
			res = digit1 - digit2;
		}
		newbigint.push_back(res + '0');
	}
	for (i; i < len_max; i++) {
		newbigint.push_back(num1[i]);
	}
	i = newbigint.length() - 1;
	while (newbigint[i] == '0' && i != 0) {
		newbigint.erase(i, 1);
		i--;
	}
	bigint = newbigint;
	return *this;
}

BigInt& BigInt::operator/=(const BigInt& n2) {
	if (n2 == BigInt(0)) {
		throw std::invalid_argument("Divivision by zero");
	}
	if (sgn == '-' && n2.sgn == '-' || sgn == '+' && n2.sgn == '+') {
		sgn = '+';
	}
	else {
		sgn = '-';
	}
	if (this->absb() < n2.absb()) {
		*this = 0;
		return *this;
	}
	std::string ans;
	std::string str1 = bigint;
	size_t len1 = str1.length();
	size_t len2 = n2.bigint.length();
	std::string sub = str1.substr(len1 - len2, len2);
	BigInt sub_b(sub, '+');
	if (sub_b < n2.absb()) {
		sub = str1[len1 - len2 - 1] + sub;
		sub_b = BigInt(sub, '+');
	}
	size_t len_first_sub = sub.length();
	int count = len1 - len_first_sub + 1;
	for (int i = 0; i < count; i++) {
		int multiplier = 0;
		int m, left = 1, right = 9;
		while (left <= right) {
			m = (left + right) / 2;
			BigInt M = m;
			M *= n2.absb();
			if (M > sub_b) {
				right = m - 1;
			}
			else {
				multiplier = m;
				left = m + 1;
			}
		}
		ans.push_back(multiplier + '0');
		BigInt Mult = multiplier;
		Mult *= n2.absb();
		sub_b -= Mult;
		if (i != count - 1) {
			if (sub_b == BigInt(0)) {
				sub = "";
			}
			else {
				sub = sub_b.bigint;
			}
			sub = str1[len1 - len_first_sub - 1 - i] + sub;
			while (sub == "0") {
				if (i == count - 2) {
					break;
				}
				ans.push_back('0');
				i++;
				sub = str1[len1 - len_first_sub - 1 - i];
			}
			if (BigInt(sub, '+') < n2.absb() && i != count - 2) {
				ans.push_back('0');
				i++;
				sub = str1[len1 - len_first_sub - 1 - i] + sub;
			}
			sub_b = BigInt(sub, '+');
		}
	}
	*this = (sgn == '-' ? -BigInt(ans) : BigInt(ans));
	return *this;
}

BigInt& BigInt::operator%=(const BigInt& n2) {
	if (n2 == BigInt(0)) {
		throw std::invalid_argument("Divivision by zero");
	}
	if (this->absb() < n2.absb()) {
		return *this;
	}
	std::string str1 = bigint;
	size_t len1 = str1.length();
	size_t len2 = n2.bigint.length();
	std::string sub;
	sub = str1.substr(len1 - len2, len2);
	BigInt sub_b(sub, '+');
	if (sub_b < n2.absb()) {
		sub = str1[len1 - len2 - 1] + sub;
		sub_b = BigInt(sub, '+');
	}
	size_t len_first_sub = sub.length();
	int count = len1 - len_first_sub + 1;
	for (int i = 0; i < count; i++) {
		int multiplier = 0;
		int m, left = 1, right = 9;
		while (left <= right) {
			m = (left + right) / 2;
			BigInt M = m;
			M *= n2.absb();
			if (M > sub_b) {
				right = m - 1;
			}
			else {
				multiplier = m;
				left = m + 1;
			}
		}
		BigInt Mult = multiplier;
		Mult *= n2.absb();
		sub_b -= Mult;
		if (i != count - 1) {
			if (sub_b == BigInt(0))
				sub = "";
			else
				sub = sub_b.bigint;
			sub = str1[len1 - len_first_sub - 1 - i] + sub;
			while (sub == "0") {
				if (i == count - 2)
					break;
				i++;
				sub = str1[len1 - len_first_sub - 1 - i];
			}
			if (BigInt(sub, '+') < n2.absb() && i != count - 2) {
				i++;
				sub = str1[len1 - len_first_sub - 1 - i] + sub;
			}
			sub_b = BigInt(sub, '+');
		}
	}
	char s = sgn;
	*this = sub_b;
	sgn = s;
	return *this;
}

BigInt& BigInt::operator^=(const BigInt& n2) {
	std::string n1_bit_str = this->bin(), n2_bit_str = n2.bin();
	size_t len1 = n1_bit_str.length();
	size_t len2 = n2_bit_str.length();
	while (len1 < len2) {
		n1_bit_str.push_back(n1_bit_str[len1 - 1]);
		len1++;
	}
	while (len2 < len1) {
		n2_bit_str.push_back(n2_bit_str[len2 - 1]);
		len2++;
	}
	n1_bit_str.push_back(n1_bit_str[len1 - 1]);
	len1++;
	n2_bit_str.push_back(n2_bit_str[len2 - 1]);
	len2++;
	std::string ans;
	for (int i = 0; i < len1; i++) {
		ans.push_back(n1_bit_str[i] == n2_bit_str[i] ? '0' : '1');
	}
	*this = dec(ans);
	return *this;
}

BigInt& BigInt::operator&=(const BigInt& n2) {
	std::string n1_bit_str = this->bin(), n2_bit_str = n2.bin();
	size_t len1 = n1_bit_str.length();
	size_t len2 = n2_bit_str.length();
	while (len1 < len2) {
		n1_bit_str.push_back(n1_bit_str[len1 - 1]);
		len1++;
	}
	while (len2 < len1) {
		n2_bit_str.push_back(n2_bit_str[len2 - 1]);
		len2++;
	}
	n1_bit_str.push_back(n1_bit_str[len1 - 1]);
	len1++;
	n2_bit_str.push_back(n2_bit_str[len2 - 1]);
	len2++;
	std::string ans;
	for (int i = 0; i < len1; i++) {
		ans.push_back((n1_bit_str[i] == '1' && n2_bit_str[i] == '1') ? '1' : '0');
	}
	*this = dec(ans);
	return *this;
}

BigInt& BigInt::operator|=(const BigInt& n2) {
	std::string n1_bit_str = this->bin(), n2_bit_str = n2.bin();
	size_t len1 = n1_bit_str.length();
	size_t len2 = n2_bit_str.length();
	while (len1 < len2) {
		n1_bit_str.push_back(n1_bit_str[len1 - 1]);
		len1++;
	}
	while (len2 < len1) {
		n2_bit_str.push_back(n2_bit_str[len2 - 1]);
		len2++;
	}
	n1_bit_str.push_back(n1_bit_str[len1 - 1]);
	len1++;
	n2_bit_str.push_back(n2_bit_str[len2 - 1]);
	len2++;
	std::string ans;
	for (int i = 0; i < len1; i++) {
		ans.push_back((n1_bit_str[i] == '1' || n2_bit_str[i] == '1') ? '1' : '0');
	}
	*this = dec(ans);
	return *this;
}

BigInt BigInt::operator+() const { // unary +
	return *this;
}

BigInt BigInt::operator-() const {  // unary -
	return BigInt(this->bigint, (sgn == '+' ? '-' : '+'));
}

bool BigInt::operator==(const BigInt& n2) const {
	return sgn == n2.sgn && bigint == n2.bigint;
}

bool BigInt::operator!=(const BigInt& n2) const {
	return !(*this == n2);
}

bool BigInt::operator<(const BigInt& n2) const {
	if (sgn == '-' && n2.sgn == '+') {
		return true;
	}
	if (sgn == '+' && n2.sgn == '-') {
		return false;
	}
	size_t len1 = bigint.length();
	size_t len2 = n2.bigint.length();
	if (len1 < len2) {
		return (sgn == '+' ? true : false);
	}
	if (len1 > len2) {
		return (sgn == '+' ? false : true);
	}
	for (int i = len1 - 1; i >= 0; i--) {
		if (bigint[i] < n2.bigint[i]) {
			return (sgn == '+' ? true : false);
		}
		if (bigint[i] > n2.bigint[i]) {
			return (sgn == '+' ? false : true);
		}
	}
	return false;
}

bool BigInt::operator>(const BigInt& n2) const {
	return !(*this <= n2);
}

bool BigInt::operator<=(const BigInt& n2) const {
	return *this < n2 || *this == n2;
}

bool BigInt::operator>=(const BigInt& n2) const {
	return !(*this < n2);
}

BigInt::operator int() const {
	int out = 0;
	int rank = 1;
	if (BigInt(INT_MIN) <= *this && *this <= BigInt(INT_MAX)) {
		size_t len = bigint.length();
		if (*this >= BigInt(0)) {
			for (int i = 0; i < len; i++) {
				out += (bigint[i] - '0') * rank;
				rank *= 10;
			}
		}
		else {
			for (int i = 0; i < len; i++) {
				out -= (bigint[i] - '0') * rank;
				rank *= 10;
			}
		}
	}
	else {
		for (int i = 0; i < 9; i++) {
			out += (bigint[i] - '0') * rank;
			rank *= 10;
		}
		if (sgn == '-') {
			out = -out;
		}
	}
	return out;
}

BigInt::operator std::string() const {
	std::string out = bigint;
	if (sgn == '-') {
		out.push_back(sgn);
	}
	std::reverse(out.begin(), out.end());
	return out;
}

size_t BigInt::size() const {
	return bigint.length() + 1;
}

BigInt BigInt::absb() const {
	return BigInt(bigint, '+');
}

std::ostream& operator<<(std::ostream& o, const BigInt& i) {
	return (o << std::string(i));
}

BigInt operator+(const BigInt& n1, const BigInt& n2) {
	BigInt ans = n1;
	ans += n2;
	return ans;
}

BigInt operator-(const BigInt& n1, const BigInt& n2) {
	BigInt ans = n1;
	ans -= n2;
	return ans;
}

BigInt operator*(const BigInt& n1, const BigInt& n2) {
	BigInt ans = n1;
	ans *= n2;
	return ans;
}

BigInt operator/(const BigInt& n1, const BigInt& n2) {
	BigInt ans = n1;
	ans /= n2;
	return ans;
}

BigInt operator%(const BigInt& n1, const BigInt& n2) {
	BigInt ans = n1;
	ans %= n2;
	return ans;
}

BigInt operator^(const BigInt& n1, const BigInt& n2) {
	BigInt ans = n1;
	ans ^= n2;
	return ans;
}

BigInt operator&(const BigInt& n1, const BigInt& n2) {
	BigInt ans = n1;
	ans &= n2;
	return ans;
}

BigInt operator|(const BigInt& n1, const BigInt& n2) {
	BigInt ans = n1;
	ans |= n2;
	return ans;
}
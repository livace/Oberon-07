#pragma once

#include "translator_visitor.h"
#include "main_generator_visitor.h"

class Translator {
public:
    void createDefaultLibrary() {
        std::ofstream out_("Lib.h");
        std::string library = R"a0(
        #include "bits/stdc++.h"

        template <class T>
        T ABS(T x) {
            return std::abs(x);
        }

        bool ODD(int x) {
            return x & 1;
        }

        template <class T>
        int LEN(const T& array) {
            return array.size();
        }

        int LSL(int x, int n) {
            return x << n;
        }

        int RSR(int x, int n) {
            return x >> n;
        }

        int ROR(int x, int n) {
            return (x >> n) | (n << (32 - n));
        }

        int FLOOR(float x) {
            return int(std::floor(x));
        }

        float FLT(int x) {
            return float(x);
        }

        template <class T>
        int ORD(T x) {
            return static_cast<int>(x);
        }

        void INC(int& x, int n = 1) {
            x += n;
        }

        void DEC(int& x, int n = 1) {
            x -= n;
        }

        void ASSERT(bool value) {
            assert(value);
        }
        template<class T>
        void NEW(T*& x) {
            x = new(T);
        }

        class __Out__ {
        public:
            void Ln() {
                std::cout << '\n';
            }

            void Int(int x, int n) {
                std::cout << std::setw(n) << x;
            }

            void Real(double x, int n) {
                std::cout << std::setw(n) << x;
            }

            void String(const char * str) {
                std::cout << str;
            }

            void Char(std::string c) {
                std::cout << c;
            }

            void Char(char c) {
                std::cout << c;
            }

            void Hex(int x) {
                std::cout << std::hex << x;
            }

            void String(const std::string& str) {
                std::cout << str;
            }
        } static Out;

        class __In__ {
            class IsDone {
            public:
                operator bool() const {
                    return std::cin.eof();
                }
            };

        public:
            void Open() {}

            void Int(int& a) {
                std::cin >> a;
            }

            IsDone Done;
        } static In;

        class Range {
        public:
            Range(int from, int to): from_(from), to_(to) {
                if (from_ > to_) {
                    std::swap(from_, to_);
                }
            }

            Range(int value): from_(value), to_(value) {}

            int from() const {
                return from_;
            }

            int to() const {
                return to_;
            }
        private:
            int from_, to_;
        };

    class FactorSet {
    public:
        FactorSet() = default;

        void Add(Range range) {
            for (int i = range.from(); i <= range.to(); ++i) {
                set_.insert(i);
            }
        }

        void Add(int value) {
            set_.insert(value);
        }

        void Remove(int value) {
            set_.erase(value);
        }

        template <class T, class... Ts>
        FactorSet(T f, Ts... rest) {
            Add(f);
            *this = *this + FactorSet(rest...);
        }

        FactorSet operator + (const FactorSet& other) const {
            FactorSet temp = *this;
            temp.set_.insert(other.set_.begin(), other.set_.end());
            return temp;
        }

        FactorSet operator - (const FactorSet& other) const {
            FactorSet temp = *this;
            for (const auto& value : other.set_) {
                temp.set_.erase(value);
            }
            return temp;
        }

        FactorSet operator * (const FactorSet& other) const {
            std::set<int> result;
            for (const auto& value : set_) {
                if (other.set_.count(value)) {
                    result.insert(value);
                }
            }
            return FactorSet(result);
        }

        FactorSet operator / (const FactorSet& other) const {
            std::set<int> result;
            for (const auto& value : set_) {
                if (!other.set_.count(value)) {
                    result.insert(value);
                }
            }
            for (const auto& value : other.set_) {
                if (!set_.count(value)) {
                    result.insert(value);
                }
            }
            return result;
        }

        bool operator == (const FactorSet& other) const {
            return other.set_ == set_;
        }

        bool operator != (const FactorSet& other) const {
            return other.set_ != set_;
        }

        void Print() const {
            for (const auto& value: set_) {
                std::cout << value << ' ';
            }
            std::cout << '\n';
        }

        friend bool operator % (const FactorSet& lhs, int i);
        friend bool operator % (int i, const FactorSet& rhs);
        private:
            FactorSet(std::set<int> set) : set_(std::move(set)) {}
            std::set<int> set_;
        };

        bool operator % (const FactorSet& lhs, int i) {
            return lhs.set_.count(i);
        }

        bool operator % (int i, const FactorSet& rhs) {
            return rhs.set_.count(i);
        }

        void INCL(FactorSet& set, int value) {
            set.Add(value);
        }

        void EXCL(FactorSet& set, int value) {
            set.Remove(value);
        }

        int RAND() {
            return rand();
        }
    )a0";
        out_ << library;
    }

    void translate(Ast *ast) {
        createDefaultLibrary();
        ast->accept(header_visitor);
        ast->accept(cpp_visitor);
    }
private:
    TranslatorVisitor header_visitor;
    MainGeneratorVisitor cpp_visitor;
};
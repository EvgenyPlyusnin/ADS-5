// Copyright 2021 NNTU-CS
#include <stdlib.h>
#include <string>
#include <map>
#include <iostream>
#include "tstack.h"

void append(char c, std::string *str) {
    *str += c;
    *str += ' ';
}

int getPriority(char c) {
    switch (c) {
        case '(':
            return 0;
        case ')':
            return 1;
        case '+':
            return 2;
        case '-':
            return 2;
        case '*':
            return 3;
        case '/':
            return 3;
        case ' ':
            return -2;
        default:
            return -1;
    }
}

int performAction(int a, int b, char c) {
    switch (c) {
        case '+':
            return b + a;
        case '-':
            return b - a;
        case '*':
            return b * a;
        case '/':
            return b / a;
        default:
            throw "Error while perform actions!";
    }
}

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack1;
    std::string res = "";
    for (int i = 0; i < inf.length(); i++) {
        if (getPriority(inf[i]) == -1) {
            if (i < inf.length() && getPriority(inf[i + 1]) == -1) {
                while (i < inf.length() && getPriority(inf[i]) == -1) {
                    res += inf[i];
                    i++;
                }
                res += ' ';
            } else {
                append(inf[i], &res);
            }
            continue;
        }
        if (stack1.isEmpty() || getPriority(inf[i]) == 0
            || getPriority(inf[i]) > getPriority(stack1.get())) {
            stack1.push(inf[i]);
        } else {
            if (getPriority(inf[i]) == 1) {
                while (getPriority(stack1.get()) != 0) {
                    append(stack1.get(), &res);
                    stack1.pop();
                }
                stack1.pop();
            } else if (getPriority(inf[i]) <= getPriority(stack1.get())) {
                while (getPriority(stack1.get()) > 1) {
                    append(stack1.get(), &res);
                    stack1.pop();
                }
                stack1.push(inf[i]);
            }
        }
    }
    while (!stack1.isEmpty()) {
        if (getPriority(stack1.get()) > 1) {
            append(stack1.get(), &res);
        }
        stack1.pop();
    }
    res.pop_back();
    return res;
}

int eval(std::string post) {
    TStack<int, 100> stack2;
    for (int i = 0; i < post.length(); i++) {
        int prohod = i;
        std::string temp = "";
        while (getPriority(post[prohod]) == -1) {
            temp += post[prohod];
            prohod++;
        }
        i = prohod;
        if (getPriority(post[i]) > 1) {
            int a = stack2.get();
            stack2.pop();
            int b = stack2.get();
            stack2.pop();
            stack2.push(performAction(a, b, post[i]));
        }
        if (temp != "") {
            stack2.push(std::stoi(temp));
        }
    }
    return stack2.get();
}

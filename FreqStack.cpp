//
// Created by kevin on 12/15/2022.
//

#ifndef CS4050_FINAL_FREQSTACK_CPP
#define CS4050_FINAL_FREQSTACK_CPP

#include <map>
#include <stack>
#include <iostream>

class FreqStack {
private:
    const int MinimumValue = 0;
    const long MaximumValue = 10E+9;
    const int MaximumCalls = 2E+4;

    int _callCount = 0;

           //count:        val: insertTimes
    std::map<int, std::map<int, std::stack<int>*>*>* _popOrder = new std::map<int, std::map<int, std::stack<int>*>*>();

    std::map<int, int>* _valueCount = new std::map<int, int>();

public:
    FreqStack() = default;

    void push(int val)
    {
        if (val > MaximumValue || val < MinimumValue || _callCount > MaximumCalls)
            throw std::exception();

        //Update count of this value
        if (_valueCount->find(val) != _valueCount->end())
        {
            _valueCount->at(val)++;
        }
        else
        {
            _valueCount->emplace(val, 1);
        }

        //If we don't have a list of vals with this count, start a list
        if (_popOrder->find(_valueCount->at(val)) == _popOrder->end())
        {
            _popOrder->emplace(_valueCount->at(val), new std::map<int, std::stack<int>*>());
        }

        //Get the current stack of this val
        std::stack<int>* valStack;
        auto previousValueCount = _valueCount->at(val) - 1;
        if (_popOrder->find(previousValueCount) != _popOrder->end() &&
        _popOrder->at(previousValueCount)->find(val) != _popOrder->at(previousValueCount)->end())
        {
            valStack = _popOrder->at(previousValueCount)->at(val);
            _popOrder->at(previousValueCount)->erase(val);
            if (_popOrder->at(previousValueCount)->empty()) //This bit may or not may not be optimal depending on data
            {
                _popOrder->erase(previousValueCount);
            }
        }
        else
        {
            valStack = new std::stack<int>();
        }
        //Update the stack
        valStack->push(_callCount++);

        //Add the stack back into the pop order
        _popOrder->at(_valueCount->at(val))->emplace(val, valStack);
    }

    int pop()
        {
            if (_popOrder->empty())
                throw std::exception();

            int result;
            //determine value to return
            auto candidates = _popOrder->rbegin()->second;
            if (candidates->size() > 1){
                result = candidates->begin()->first;
                int newestCall = 0;
                for (auto & candidate : *candidates) {
                    if (candidate.second->top() > newestCall){
                        newestCall = candidate.second->top();
                        result = candidate.first;
                    }
                }
            } else{
                result = candidates->begin()->first;
            }

            //update value stack
            _popOrder->at(_valueCount->at(result))->at(result)->pop();

            //remove value stack from current position
            std::stack<int>* valStack = _popOrder->at(_valueCount->at(result))->at(result);
            _popOrder->at(_valueCount->at(result))->erase(result);
            if (_popOrder->at(_valueCount->at(result))->empty()){
                _popOrder->erase(_valueCount->at(result));
            }

            //decrement value count
            _valueCount->at(result)--;

            //Either cleanup empty value or add back to popOrder
            if (valStack->empty()){
                _valueCount->erase(result);
            } else
            {
                if (_popOrder->find(_valueCount->at(result)) == _popOrder->end())
                {
                    _popOrder->emplace(_valueCount->at(result), new std::map<int, std::stack<int>*>());
                }
                _popOrder->at(_valueCount->at(result))->emplace(result, valStack);
            }

            return result;
        }
};

int main(){
    auto obj = FreqStack();

    obj.push(5);
    obj.push(1);
    obj.push(2);
    obj.push(5);
    obj.push(5);
    obj.push(5);
    obj.push(1);
    obj.push(6);
    obj.push(1);
    obj.push(5);
    std::cout << obj.pop() << std::endl;
    std::cout << obj.pop() << std::endl;
    std::cout << obj.pop() << std::endl;
    std::cout << obj.pop() << std::endl;
    std::cout << obj.pop() << std::endl;
    std::cout << obj.pop() << std::endl;
    std::cout << obj.pop() << std::endl;
    std::cout << obj.pop() << std::endl;
    std::cout << obj.pop() << std::endl;
    std::cout << obj.pop() << std::endl;
}


#endif //CS4050_FINAL_FREQSTACK_CPP

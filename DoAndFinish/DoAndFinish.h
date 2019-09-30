#pragma once
#include <functional>

template <
    typename ...DoFuncArgs,
    typename ShouldFinish,
    typename Finish>
auto DoAndFinish(
     std::function<void(DoFuncArgs)> doFunc,
     ShouldFinish &&shouldFinishFunc,
     std::function<void(DoFuncArgs)> finishFunc) 
{
    return [ doFunc{std::forward<Do>(doFunc)}, 
             shouldFinishFunc{std::forward<ShouldFinish>(shouldFinishFunc)},
             finishFunc{std::forward<Finish>(finishFunc)} ] (DoFuncArgs ...args)
             {
                 if(shouldFinishFunc()) 
                 {
                     finishFunc(args...);
                 }
                 doFunc(args...);
                 return finishFunc;
             };
}

#pragma once

template <typename Do, typename ...DoFuncArgs, typename ShouldFinish, typename Finish>
auto DoAndFinish( Do &&doFunc(DoFuncArgs...), ShouldFinish &&shouldFinishFunc, Finish &&finishFunc(DoFuncArgs...)) 
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
             };
}

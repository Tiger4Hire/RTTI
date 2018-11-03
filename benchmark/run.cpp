#include <benchmark/benchmark.h>
#include <variant>
#include "ObjectList.h"

using OldList = std::list<std::unique_ptr<Object>>;
using AltList = std::vector<std::variant<TextLabel, Button>>;

OldList MakeOld(int size)
{
    OldList retval;
    for (int i = 0; i < size; ++i)
        if (rand() & 1)
            retval.push_back(std::make_unique<TextLabel>(""));
        else
            retval.push_back(std::make_unique<Button>());

    return retval;
}

AltList MakeAlt(int size)
{
    AltList retval;
    for (int i = 0; i < size; ++i)
        if (rand() & 1)
            retval.emplace_back(TextLabel(""));
        else
            retval.emplace_back(Button());

    return retval;
}

ObjectList MakeNew(int size)
{
    ObjectList retval;
    for (int i = 0; i < size; ++i)
        if (rand() & 1)
            retval.emplace_back(TextLabel(""));
        else
            retval.emplace_back(Button());
    return retval;
}

static void BM_OldList(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        state.SetComplexityN(state.range(0));
        OldList oldList = MakeOld(state.range(0));
        state.ResumeTiming();
        for (auto& elem : oldList)
            elem->DoNothing();
    }
}
static void BM_AltList(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        state.SetComplexityN(state.range(0));
        AltList altList = MakeAlt(state.range(0));
        state.ResumeTiming();
        for (const auto& obj : altList)
            std::visit([](const auto& v) { v.DoNothing(); }, obj);
    }
}
static void BM_NewList(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        state.SetComplexityN(state.range(0));
        ObjectList newList = MakeNew(state.range(0));
        state.ResumeTiming();
        newList.visit([count = 0](const auto& v) { v.DoNothing(); });
    }
}
// Register the function as a benchmark
BENCHMARK(BM_OldList)->Arg(100)->Arg(500)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(500000)->Complexity();
BENCHMARK(BM_AltList)->Arg(100)->Arg(500)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(500000)->Complexity();
BENCHMARK(BM_NewList)->Arg(100)->Arg(500)->Arg(1000)->Arg(10000)->Arg(100000)->Arg(500000)->Complexity();

BENCHMARK_MAIN();
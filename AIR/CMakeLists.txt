cmake_minimum_required(VERSION 3.15)
project(AIR)

set(CMAKE_CXX_STANDARD 14)

set(COMPILER_PATH "/usr/bin") # or /usr/local/bin
find_package(PythonLibs REQUIRED)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS})

set(CMAKE_CXX_COMPILER "${COMPILER_PATH}/mpic++")
link_directories(/usr/lib/gcc/x86_64-linux-gnu/9)

include_directories(/usr/local/include)
include_directories(include)
include_directories(include/json)
include_directories(src/batching)
include_directories(src/collector)
include_directories(src/communication)
include_directories(src/configuration)
include_directories(src/connector)
include_directories(src/dataflow)
include_directories(src/function)
include_directories(src/input)
include_directories(src/output)
include_directories(src/partitioning)
include_directories(src/relational)
include_directories(src/serialization)
include_directories(src/usecases)
include_directories(src/winagg)
include_directories(src/yahoo)
include_directories(src/yahoo_m)

add_executable(AIR
        src/batching/Map.cpp
        src/batching/Map.hpp
        src/batching/Reduce.cpp
        src/batching/Reduce.hpp
        src/collector/BinCollector.cpp
        src/collector/BinCollector.hpp
        src/collector/RowCollector.cpp
        src/collector/RowCollector.hpp
        src/communication/Message.cpp
        src/communication/Message.hpp
        src/communication/Window.cpp
        src/communication/Window.hpp
        src/configuration/HashConfig.hpp
        src/connector/BinConnector.cpp
        src/connector/BinConnector.hpp
        src/connector/PartRowConnector.cpp
        src/connector/PartRowConnector.hpp
        src/connector/RowConnector.cpp
        src/connector/RowConnector.hpp
        src/dataflow/Dataflow.cpp
        src/dataflow/Dataflow.hpp
        src/dataflow/Vertex.cpp
        src/dataflow/Vertex.hpp
        src/function/Function.cpp
        src/function/Function.hpp
        src/function/SquareFunction.cpp
        src/function/SquareFunction.hpp
        src/function/SumFunction.cpp
        src/function/SumFunction.hpp
        src/input/FileInput.cpp
        src/input/FileInput.hpp
        src/input/Input.cpp
        src/input/Input.hpp
        src/main/main.cpp
        src/output/FileOutput.cpp
        src/output/FileOutput.hpp
        src/output/Output.cpp
        src/output/Output.hpp
        src/partitioning/Hash.cpp
        src/partitioning/Hash.hpp
        src/partitioning/PairPartition.hpp
        src/partitioning/Partition.hpp
        src/relational/Aggr.cpp
        src/relational/Aggr.hpp
        src/relational/Attribute.cpp
        src/relational/Attribute.hpp
        src/relational/Cond.cpp
        src/relational/Cond.hpp
        src/relational/Relation.cpp
        src/relational/Relation.hpp
        src/relational/Schema.cpp
        src/relational/Schema.hpp
        src/relational/SortAggregation.cpp
        src/relational/SortAggregation.hpp
        src/relational/SortMergeJoin.cpp
        src/relational/SortMergeJoin.hpp
        src/serialization/Serialization.cpp
        src/serialization/Serialization.hpp
        src/usecases/MapReduce.cpp
        src/usecases/MapReduce.hpp
        src/usecases/StreamingTest.cpp
        src/usecases/StreamingTest.hpp
        src/usecases/TPCH.cpp
        src/usecases/TPCH.hpp
        src/usecases/WinAgg.cpp
        src/usecases/WinAgg.hpp
        src/usecases/YSB.cpp
        src/usecases/YSB.hpp
        src/usecases/ReasonAIR.cpp
        src/usecases/ReasonAIR.hpp
        src/usecases/YSB_m.cpp
        src/usecases/YSB_m.hpp
        src/winagg/EventSharder.cpp
        src/winagg/EventSharder.hpp
        src/winagg/WindowedCounter.cpp
        src/winagg/WindowedCounter.hpp
        src/yahoo/EventCollector.cpp
        src/yahoo/EventCollector.hpp
        src/yahoo/EventFilter.cpp
        src/yahoo/EventFilter.hpp
         src/yahoo/Reasoner.cpp
        src/yahoo/Reasoner.hpp
        src/yahoo/EventGenerator.cpp
        src/yahoo/EventGenerator.hpp
        src/yahoo/OWLEventGenerator.cpp
        src/yahoo/OWLEventGenerator.hpp
        src/yahoo/FullAggregator.cpp
        src/yahoo/FullAggregator.hpp
        src/yahoo/PartialAggregator.cpp
        src/yahoo/PartialAggregator.hpp
        src/yahoo/SHJoin.cpp
        src/yahoo/SHJoin.hpp
        src/yahoo_m/EventFilter_m.cpp
        src/yahoo_m/EventFilter_m.hpp
        src/yahoo_m/FullAggregator_m.cpp
        src/yahoo_m/FullAggregator_m.hpp
        src/yahoo_m/WinJoinYSB_m.cpp
        src/yahoo_m/WinJoinYSB_m.hpp)
        
        
        
target_link_libraries(AIR ${PYTHON_LIBRARIES})

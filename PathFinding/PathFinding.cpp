#include <iostream>
#include <ctime>

#include "Graph.h"

int main()
{
    clock_t start, end;
    start = clock();

    CGraph* graph = new CGraph();

    graph->ParsingXMLFiles();
    graph->ParsingFileCalledMakeBlock();
    graph->Test();                          // ²âÊÔ¿ªÊ¼

    delete graph;

    end = clock();
    std::cout << "time = " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;

    return 0;
}
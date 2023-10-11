#pragma once
#ifndef _GRAPH_H__
#define _GRAPH_H__

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <unordered_map>

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/sax/HandlerBase.hpp>
XERCES_CPP_NAMESPACE_USE

#include "Segment.h"
#include "Node.h"
#include "Block.h"
#include "Bridge.h"
#include "tinyxml2.h"

class CGraph
{
public:
    CGraph();

    void DebugOfSegments();
    void DebugOfNodes();
    void DebugOfBlocks();

    void ParsingXMLFiles(); // 解析XML文件
    void ParsingFileCalledMakeBlock(); // 解析 点与块对应
    std::vector<double> AStarForGraph(int, int, int); // 先求出块的路径，根据块求点，返回具体路径 + 时间

    void Test();
private:
    DOMNode* findchildNode(DOMNode*, const char*);
    // 得到的都是箭头所指方向的角度
    double GetSegmentDirection1(int, int); // 得到一个线段 start ------ end -> 的方向
    double GetSegmentDirection2(int, int); // 得到一个线段 -> start ------ end 的方向 
    bool CheckSegment(int, int, int); // 根据上面两个函数来检测 x -> y -> z 能不能通行（曲率是否一致）

    double HForAStar(double, double, double, double); // 计算曼哈顿距离作为估值函数
    CNode AStarForBlock(CNode, CNode, int, int, int, std::vector<double>&); // 块内的 AStar 
    void Dijkstra(int, int, int, std::vector<double>&);
    int FindNodeByID(int);
    CSegment FindSegmentByID(int, int);
    CBridge FindBridgeByID(int, int);
    int FindTheFirstIndexOfTheEdgeNeighbor(int);
    int FindTheLastIndexOfTheEdgeNeighbor(int);
    int FindTheFirstIndexOfTheBlockNeighbor(int);
    int FindTheLastIndexOfTheBlockNeighbor(int);

private:
    std::vector<CSegment> Segments;
    std::vector<CNode> Nodes;
    std::vector<CBlock> Blocks;
    std::vector<CBridge> Bridges;
};

#endif // _GRAPH_H__
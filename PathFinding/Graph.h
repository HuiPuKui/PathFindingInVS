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

    void ParsingXMLFiles(); // ����XML�ļ�
    void ParsingFileCalledMakeBlock(); // ���� ������Ӧ
    std::vector<double> AStarForGraph(int, int, int); // ��������·�������ݿ���㣬���ؾ���·�� + ʱ��

    void Test();
private:
    DOMNode* findchildNode(DOMNode*, const char*);
    // �õ��Ķ��Ǽ�ͷ��ָ����ĽǶ�
    double GetSegmentDirection1(int, int); // �õ�һ���߶� start ------ end -> �ķ���
    double GetSegmentDirection2(int, int); // �õ�һ���߶� -> start ------ end �ķ��� 
    bool CheckSegment(int, int, int); // ��������������������� x -> y -> z �ܲ���ͨ�У������Ƿ�һ�£�

    double HForAStar(double, double, double, double); // ���������پ�����Ϊ��ֵ����
    CNode AStarForBlock(CNode, CNode, int, int, int, std::vector<double>&); // ���ڵ� AStar 
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
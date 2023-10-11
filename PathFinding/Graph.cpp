#include "Graph.h"

/**
 * 构造函数初始化
 */

int TheMaxNumberOfBlock = 12;

CGraph::CGraph() : Blocks(TheMaxNumberOfBlock + 1)
{
    Segments.clear();
    Nodes.clear();
    Bridges.clear();
}

void CGraph::Test()
{
    std::ofstream out("../TxtFile/AnswerOfMap_Sinocare2.txt");
    for (int i = 0; i < Nodes.size(); ++i)
    {
        std::cout << Nodes[i].GetID() << std::endl;
        for (int j = 0; j < Nodes.size(); ++j)
        {
            int l = Nodes[i].GetID();
            int r = Nodes[j].GetID();
            out << l << ' ' << r << '\n';
            std::vector<double> Ans = AStarForGraph(l, r, 1);
            for (auto x : Ans)
            {
                out << x << ' ';
            }
            out << '\n' << "---  ---  ---" << '\n';
        }
    }
    out.close();

    //std::vector<double> Ans = AStarForGraph(1, 91, 1);
    //for (auto x : Ans) std::cout << x << ' ';
    //std::cout << std::endl;
}

DOMNode* CGraph::findchildNode(DOMNode* n, const char* nodename)
{
    //寻找n节点下子节点名为nodename的节点
    try
    {
        for (DOMNode* child = n->getFirstChild(); child != 0; child = child->getNextSibling())
        {
            if (child->getNodeType() == DOMNode::ELEMENT_NODE && XMLString::compareString(child->getNodeName(), XMLString::transcode(nodename)) == 0)
            {
                return child;
            }
        }
    }
    catch (const XMLException& toCatch)
    {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
    }
    return 0;
}

/**
 * 解析 XML 文件
 */

void CGraph::ParsingXMLFiles()
{
    try 
    {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) 
    {
        return;
    }

    XercesDOMParser * parser = new XercesDOMParser();
    parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setDoNamespaces(true);    
    
    ErrorHandler * errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

    try 
    {
        parser->parse("Map_Sinocare.xml");
    }
    catch (const XMLException& toCatch) 
    {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return;
    }
    catch (const DOMException& toCatch) 
    {
        char* message = XMLString::transcode(toCatch.msg);
        std::cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return;
    }
    catch (...) 
    {
        std::cout << "Unexpected Exception \n";
        return;
    }

    DOMDocument* doc = parser->getDocument();
    DOMElement * root = doc->getDocumentElement();

    DOMNode* DN = root;
    DN = findchildNode(DN, "Nodes");

    for (DN = DN->getFirstChild(); DN != 0; DN = DN->getNextSibling())
    {
        if (DN->getNodeType() == DOMNode::ELEMENT_NODE)
        {
            CNode Temp;
            Temp.SetID(std::stoi(XMLString::transcode(findchildNode(DN, "ID")->getTextContent())));
            Temp.SetNodeType(std::stoi(XMLString::transcode(findchildNode(DN, "NodeType")->getTextContent())));
            Temp.SetX(std::stod(XMLString::transcode(findchildNode(DN, "X")->getTextContent())));
            Temp.SetY(std::stod(XMLString::transcode(findchildNode(DN, "Y")->getTextContent())));
            Temp.SetHeading(std::stod(XMLString::transcode(findchildNode(DN, "Heading")->getTextContent())));
            Temp.SetObstacle(std::stoi(XMLString::transcode(findchildNode(DN, "Obstacle")->getTextContent())));
            Temp.SetCheckMarkDistance(std::stod(XMLString::transcode(findchildNode(DN, "CheckMarkDistance")->getTextContent())));
            Temp.SetCheckMarkVelocity(std::stod(XMLString::transcode(findchildNode(DN, "CheckMarkVelocity")->getTextContent())));
            std::string RFID = XMLString::transcode(findchildNode(DN, "RFID")->getTextContent());
            if (RFID.size())
            {
                Temp.SetRFID(std::stoi(XMLString::transcode(findchildNode(DN, "RFID")->getTextContent())));
            }
            else
            {
                Temp.SetRFID(0);
            }
            Nodes.push_back(Temp);
        }
    }
    std::sort(Nodes.begin(), Nodes.end());

    DN = root;
    DN = findchildNode(DN, "Segments");

    for (DN = DN->getFirstChild(); DN != 0; DN = DN->getNextSibling())
    {
        if (DN->getNodeType() == DOMNode::ELEMENT_NODE)
        {
            CSegment Temp;
            Temp.SetID(std::stoi(XMLString::transcode(findchildNode(DN, "ID")->getTextContent())));
            Temp.SetType(std::stoi(XMLString::transcode(findchildNode(DN, "Type")->getTextContent())));
            Temp.SetWayType(std::stoi(XMLString::transcode(findchildNode(DN, "WayType")->getTextContent())));
            Temp.SetStartNodeID(std::stoi(XMLString::transcode(findchildNode(DN, "StartNodeID")->getTextContent())));
            Temp.SetEndNodeID(std::stoi(XMLString::transcode(findchildNode(DN, "EndNodeID")->getTextContent())));
            Temp.SetVelocityLimit1(std::stod(XMLString::transcode(findchildNode(DN, "VelocityLimit1")->getTextContent())));
            Temp.SetVelocityLimit2(std::stod(XMLString::transcode(findchildNode(DN, "VelocityLimit2")->getTextContent())));
            Temp.SetDeadReckonDis(std::stod(XMLString::transcode(findchildNode(DN, "DeadReckonDis")->getTextContent())));
            Temp.SetObstacle(std::stoi(XMLString::transcode(findchildNode(DN, "Obstacle")->getTextContent())));
            Temp.SetGuideType(std::stoi(XMLString::transcode(findchildNode(DN, "GuideType")->getTextContent())));
            Temp.SetDirection(std::stoi(XMLString::transcode(findchildNode(DN, "Direction")->getTextContent())));

            if (Temp.GetType() == 1)
            {
                Temp.SetSize(std::stod(XMLString::transcode(findchildNode(DN, "Size")->getTextContent())));
                Temp.SetSlantAngle(std::stod(XMLString::transcode(findchildNode(DN, "SlantAngle")->getTextContent())));
                Temp.SetFlexible(std::stoi(XMLString::transcode(findchildNode(DN, "Flexible")->getTextContent())));
            }
            else if (Temp.GetType() == 3)
            {
                Temp.SetArcDirection(std::stoi(XMLString::transcode(findchildNode(DN, "ArcDirection")->getTextContent())));
                Temp.SetCentralX(std::stod(XMLString::transcode(findchildNode(DN, "CentralX")->getTextContent())));
                Temp.SetCentralY(std::stod(XMLString::transcode(findchildNode(DN, "CentralY")->getTextContent())));
                Temp.SetRadius(std::stod(XMLString::transcode(findchildNode(DN, "Radius")->getTextContent())));
                Temp.SetStartAngle(std::stod(XMLString::transcode(findchildNode(DN, "StartAngle")->getTextContent())));
                Temp.SetEndAngle(std::stod(XMLString::transcode(findchildNode(DN, "EndAngle")->getTextContent())));

                // 圆弧计算边长度要根据顺时针、逆时针来判断是优弧还是劣弧

                double Angle = (Temp.GetStartAngle() - Temp.GetEndAngle());
                if (Temp.GetArcDirection() == 0)
                {
                    Angle = -Angle;
                }
                if (Angle < 0)
                {
                    Angle += 360;
                }

                Temp.SetSize(fabs(2.0 * acos(-1) * Temp.GetRadius() * Angle * 1.0 / 360));
            }
            else if (Temp.GetType() == 4) // S 形曲线：长度使用欧几里得距离计算
            {
                Temp.SetStartHeading(std::stod(XMLString::transcode(findchildNode(DN, "StartHeading")->getTextContent())));
                double Deltax = Nodes[FindNodeByID(Temp.GetStartNodeID())].GetX() - Nodes[FindNodeByID(Temp.GetEndNodeID())].GetX();
                double Deltay = Nodes[FindNodeByID(Temp.GetStartNodeID())].GetY() - Nodes[FindNodeByID(Temp.GetEndNodeID())].GetY();
                Temp.SetSize(fabs(sqrt(Deltax * Deltax + Deltay * Deltay)));
                Temp.SetSlantAngle(Temp.GetStartHeading());
            }
            else
            {
                std::cout << "new Type" << std::endl;
            }
            Temp.SetIsReverseEdge(0);

            if (Temp.GetDirection() == 1)
            {
                Temp.SetSize(Temp.GetSize() * 2.5);
            }

            Segments.push_back(Temp);

            if (Temp.GetWayType() == 1)
            {
                Temp.SwapNodes();
                if (Temp.GetDirection() == 0)
                {
                    Temp.SetSize(Temp.GetSize() * 2.5);
                }
                else
                {
                    Temp.SetSize(Temp.GetSize() / 2.5);
                }
                Temp.SetIsReverseEdge(1);
                Segments.push_back(Temp);
            }
        }
    }
    std::sort(Segments.begin(), Segments.end());

    XMLPlatformUtils::Terminate();
}

/**
 * 解析 MakeBlock 文件
 */

void CGraph::ParsingFileCalledMakeBlock()
{
    for (int i = 0; i <= TheMaxNumberOfBlock; ++i) // 在解析文件之前先初始化块
    {
        Blocks[i].SetID(i);
        Blocks[i].SetX(0);
        Blocks[i].SetY(0);
        Blocks[i].SetCount(0);
    }

    std::ifstream infile;
    infile.open("Map_Sinocare.txt", std::ios::in);

    std::string str;
    while (getline(infile, str))
    {
        // 文件内的格式是 X:Y  X：为块的ID，Y：为属于 X 的点的ID
        int Index = (int)str.find(":"); // 找到 ":" 分隔符
        std::string strValue = str.substr(0, Index);
        std::string strKey = str.substr(Index + 1);
        int iKey = std::stoi(strKey);
        int iValue = std::stoi(strValue);
        Nodes[FindNodeByID(iKey)].SetWhichBlock(iValue);
        Blocks[iValue].SetX((Blocks[iValue].GetX() * Blocks[iValue].GetCount() + Nodes[FindNodeByID(iKey)].GetX()) * 1.0 / (Blocks[iValue].GetCount() + 1));
        Blocks[iValue].SetY((Blocks[iValue].GetY() * Blocks[iValue].GetCount() + Nodes[FindNodeByID(iKey)].GetY()) * 1.0 / (Blocks[iValue].GetCount() + 1));
        Blocks[iValue].SetCount(Blocks[iValue].GetCount() + 1);
    }
    infile.close();

    for (int i = 0; i < Segments.size(); ++i)
    {
        int Start = Segments[i].GetStartNodeID();
        int End = Segments[i].GetEndNodeID();
        CNode StartNode = Nodes[FindNodeByID(Start)];
        CNode EndNode = Nodes[FindNodeByID(End)];
        if (StartNode.GetWhichBlock() != EndNode.GetWhichBlock()) // 只有这条边的两个端点分别属于不同的块时，才可以为块图加边
        {
            CBridge Temp;
            Temp.SetStartBlockID(StartNode.GetWhichBlock());
            Temp.SetEndBlockID(EndNode.GetWhichBlock());
            Temp.SetMultiple(Segments[i].GetIsReverseEdge() == 1 ? 2 : 1);
            Bridges.push_back(Temp);
        }
    }

    std::sort(Bridges.begin(), Bridges.end());
}

/**
 * 通过 ID 找点
 */

int CGraph::FindNodeByID(int ID)
{
    int l = 0;
    int r = (int)Nodes.size() - 1;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (Nodes[mid].GetID() >= ID)
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    return l;
}

/**
 * 通过 ID 找线段
 */

CSegment CGraph::FindSegmentByID(int Start, int End)
{
    int l = 0;
    int r = (int)Segments.size() - 1;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (Segments[mid].GetStartNodeID() > Start || (Segments[mid].GetStartNodeID() == Start && Segments[mid].GetEndNodeID() >= End))
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    return Segments[l];
}

/**
 * 通过 ID 找桥
 */

CBridge CGraph::FindBridgeByID(int Start, int End)
{
    int l = 0;
    int r = (int)Bridges.size() - 1;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (Bridges[mid].GetStartBlockID() > Start || (Bridges[mid].GetStartBlockID() == Start && Bridges[mid].GetEndBlockID() >= End))
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    return Bridges[l];
}

/**
 * 二分找图的邻边（最左）
 */

int CGraph::FindTheFirstIndexOfTheEdgeNeighbor(int ID)
{
    int l = 0;
    int r = (int)Segments.size() - 1;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (Segments[mid].GetStartNodeID() >= ID)
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    return l;
}

/**
 * 二分找图的邻边（最右）
 */

int CGraph::FindTheLastIndexOfTheEdgeNeighbor(int ID)
{
    int l = 0;
    int r = (int)Segments.size() - 1;
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (Segments[mid].GetStartNodeID() <= ID)
        {
            l = mid;
        }
        else
        {
            r = mid - 1;
        }
    }
    return l;
}

/**
 * 二分找块的邻边（最左）
 */

int CGraph::FindTheFirstIndexOfTheBlockNeighbor(int ID)
{
    int l = 0;
    int r = (int)Bridges.size() - 1;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (Bridges[mid].GetStartBlockID() >= ID)
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    return l;
}

/**
 * 二分找块的邻边（最右）
 */

int CGraph::FindTheLastIndexOfTheBlockNeighbor(int ID)
{
    int l = 0;
    int r = (int)Bridges.size() - 1;
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (Bridges[mid].GetStartBlockID() <= ID)
        {
            l = mid;
        }
        else
        {
            r = mid - 1;
        }
    }
    return l;
}

/**
 * 估值函数 计算曼哈顿距离
 */

double CGraph::HForAStar(double xl, double yl, double xr, double yr)
{
    double DeltaX = fabs(xl - xr);
    double DeltaY = fabs(yl - yr);
    return DeltaX + DeltaY;
}

/**
 * 找 Start --- End -> 的方向
 */

double CGraph::GetSegmentDirection1(int Start, int End)
{
    CSegment NowSegment = FindSegmentByID(Start, End);
    if (NowSegment.GetIsReverseEdge() == 1)
    {
        NowSegment.SwapNodes();
    }

    double NowDirection = 0;
    if (NowSegment.GetType() == 1 || NowSegment.GetType() == 4) // 直线
    {
        NowDirection = NowSegment.GetSlantAngle();
        // 正向 且 End To Start 或 反向 且 Start To End
        if ((Start == NowSegment.GetStartNodeID() && NowSegment.GetDirection() == 1) || (Start == NowSegment.GetEndNodeID() && NowSegment.GetDirection() == 0))
        {
            NowDirection += 180;
        }
    }
    else if (NowSegment.GetType() == 3) // 圆弧
    {
        if (Start == NowSegment.GetStartNodeID()) // 正向
        {
            NowDirection = NowSegment.GetEndAngle();
            NowDirection += NowSegment.GetArcDirection() == 0 ? 90 : 270;
        }
        else if (Start == NowSegment.GetEndNodeID()) // 反向
        {
            NowDirection = NowSegment.GetStartAngle();
            NowDirection += NowSegment.GetArcDirection() == 0 ? 270 : 90;
        }
    }

    if (NowDirection >= 360)
    {
        NowDirection -= 360;
    }

    return NowDirection;
}

/**
 * 找 -> Start ------ End 的方向
 */

double CGraph::GetSegmentDirection2(int Start, int End)
{
    CSegment NowSegment = FindSegmentByID(Start, End);
    if (NowSegment.GetIsReverseEdge() == 1)
    {
        NowSegment.SwapNodes();
    }

    double NowDirection = 0;
    if (NowSegment.GetType() == 1 || NowSegment.GetType() == 4) // 直线
    {
        NowDirection = NowSegment.GetSlantAngle();
        // 正向 且 End To Start 或 反向 且 Start To End
        if ((Start == NowSegment.GetStartNodeID() && NowSegment.GetDirection() == 1) || (Start == NowSegment.GetEndNodeID() && NowSegment.GetDirection() == 0))
        {
            NowDirection += 180;
        }
    }
    else if (NowSegment.GetType() == 3) // 圆弧
    {
        if (Start == NowSegment.GetStartNodeID()) // 正向
        {
            NowDirection = NowSegment.GetStartAngle();
            NowDirection += NowSegment.GetArcDirection() == 0 ? 90 : 270;
        }
        else if (Start == NowSegment.GetEndNodeID()) // 反向
        {
            NowDirection = NowSegment.GetEndAngle();
            NowDirection += NowSegment.GetArcDirection() == 0 ? 270 : 90;
        }
    }

    if (NowDirection >= 360)
    {
        NowDirection -= 360;
    }

    return NowDirection;
}

/**
 * 看小车是否可以从 Previous --->--- Now 走到 Now --->--- Next 这条边 （曲率是否相同）
 */

bool CGraph::CheckSegment(int Previous, int Now, int Next)
{
    double PreviousDirection = GetSegmentDirection1(Previous, Now);
    double NextDirection = GetSegmentDirection2(Now, Next);
    double Answer = (double)fabs(PreviousDirection - NextDirection);
    return (double)Answer < 0.1 || (double)fabs(360 - Answer) < 0.1 || (double)fabs(180 - Answer) < 0.1;
}

/**
 * 求块路径的 A* 算法（起始点，终止点，下一个必经块的ID，终点块的ID，能否自旋，返回结果的引用）
 */

CNode CGraph::AStarForBlock(CNode Start, CNode End, int NextBlockNumber, int EndBlockNumber, int TypeOfCar, std::vector<double>& Result)
{
    std::unordered_map<double, double> Close; // 记录所有点的上一个某个角度的节点是什么

    int StartNode = Start.GetID();
    int StartBlock = Nodes[FindNodeByID(StartNode)].GetWhichBlock();

    typedef std::pair<double, std::pair<double, double> > PDDD;
    std::priority_queue<PDDD, std::vector<PDDD>, std::greater<PDDD> > Open; // 整体预估值，起点到目前的真实距离，此时点的id

    Open.push({ HForAStar(Start.GetX(), Start.GetY(), End.GetX(), End.GetY()), {0, StartNode * 1000 * 1.0} });

    while (!Open.empty())
    {
        PDDD Now = Open.top();
        Open.pop();

        //std::cout << "From:" << Now.second.second << ' ' << Now.second.first << std::endl;

        int NodeID = (int)(Now.second.second / 1000);
        if ((StartBlock == EndBlockNumber && NodeID == End.GetID()) || (StartBlock != EndBlockNumber && Nodes[FindNodeByID(NodeID)].GetWhichBlock() == NextBlockNumber)) // 如果目前这个点和终点处于同一个块的话
        {
            double Back = Now.second.second;
            int ResultSize = Result.size();
            while (Close.count(Back) && Close[Back] != -1)
            {
                Result.push_back((int)Back / 1000);
                Back = Close[Back];
            }
            if (ResultSize == 0 || (ResultSize && Result[ResultSize - 1] != Back / 1000)) // 判断此时的点和上一次搜索结果衔接的时候会不会重复
            {
                Result.push_back((int)Back / (int)1000);
            }
            reverse(Result.begin() + ResultSize, Result.end());
            return Nodes[FindNodeByID(NodeID)];
        }

        if (Nodes[FindNodeByID(NodeID)].GetWhichBlock() != StartBlock) // 如果在搜索的时候跑出了这个块就断掉
        {
            continue;
        }

        int BeginIndex = FindTheFirstIndexOfTheEdgeNeighbor(NodeID);
        int EndIndex = FindTheLastIndexOfTheEdgeNeighbor(NodeID);

        for (int i = BeginIndex; i <= EndIndex; ++i)
        {
            int Last = Segments[i].GetEndNodeID();
            double Direction = GetSegmentDirection2(Last, NodeID); // 对于 X -> Y -> Z 找到 X -> Y 的曲率
            double Direction2 = GetSegmentDirection2(NodeID, Last); // 对于 X -> Y -> Z 找到 Y -> Z 的曲率
            if (Close.count(Last * 1000 * 1.0 + Direction)) // 如果此时点的这个方向被走过就不用再走了
            {
                continue;
            }
            if (TypeOfCar == 1 && NodeID != Start.GetID() && CheckSegment((int)Close[Now.second.second] / 1000, NodeID, Last) == false) // 如果车子无法自旋且不是第一个点（因为第一个点没有走来的点，没法判断两段曲率）并且曲率不同
            {
                continue;
            }

            //std::cout << "To:" << Last << ' ' << Now.second.first << ' ' << Segments[i].GetSize() << std::endl;

            Close[Last * 1000 * 1.0 + Direction] = Now.second.second;
            // 防止死循环，这个点正/反向走过，就不能反/正向走了，否者回溯路径的时候会产生环导致死循环
            if (!Close.count(NodeID * 1000 * 1.0 + Direction2))
            {
                Close[NodeID * 1000 * 1.0 + Direction2] = -1;
            }
            // 预估值：起点到此点的真实距离 + 点到下一个点的真实距离 + 下一个点到终点的估值，真实值：起点到此点的真实距离 + 点到下一个点的真实距离，ID：下一个点的 ID
            Open.push({ Now.second.first + Segments[i].GetSize() + HForAStar(Nodes[FindNodeByID(Last)].GetX(), Nodes[FindNodeByID(Last)].GetY(), End.GetX(), End.GetY()),
                      {Now.second.first + Segments[i].GetSize(), Last * 1000 * 1.0 + Direction} });
        }
    }

    CNode NoPath;
    NoPath.SetID(-1);
    return NoPath;
}

void CGraph::Dijkstra(int Start, int End, int TypeOfCar, std::vector<double>& Result)
{
    std::unordered_map<int, int> AllPath;
    std::vector<bool> IsVisited(Nodes.size() + 1, false); // 是否被访问
    std::vector<double> Distance(Nodes.size() + 1, 0x3f3f3f3f); // 路径长度

    typedef std::pair<double, int> PDI;
    std::priority_queue<PDI, std::vector<PDI>, std::greater<PDI> > Open;

    Open.push({ 0, Start });
    Distance[FindNodeByID(Start)] = 0;
    AllPath[Start] = -1;

    while (!Open.empty())
    {
        PDI Now = Open.top();
        Open.pop();

        if (IsVisited[FindNodeByID(Now.second)])
        {
            continue;
        }
        IsVisited[FindNodeByID(Now.second)] = true;

        int BeginIndex = FindTheFirstIndexOfTheEdgeNeighbor(Now.second);
        int EndIndex = FindTheLastIndexOfTheEdgeNeighbor(Now.second);

        for (int i = BeginIndex; i <= EndIndex; ++i)
        {
            if (TypeOfCar == 1 && Now.second != Start && CheckSegment(AllPath[Now.second], Now.second, Segments[i].GetEndNodeID()) == false) // 如果车子无法自旋且不是第一个点（因为第一个点没有走来的点，没法判断两段曲率）并且曲率不同
            {
                continue;
            }

            int Index = FindNodeByID(Segments[i].GetEndNodeID());

            if (Distance[Index] > Now.first + Segments[i].GetSize())
            {
                Distance[Index] = Now.first + Segments[i].GetSize();
                Open.push({ Distance[Index], Segments[i].GetEndNodeID() });
                AllPath[Segments[i].GetEndNodeID()] = Now.second;
            }
        }
    }

    int Back = End;
    while (AllPath[Back] != -1) // 路径回溯
    {
        Result.push_back(Back);
        Back = AllPath[Back];
    }
    Result.push_back(Back);
    reverse(Result.begin(), Result.end());
}

/**
 * 求整体路径的 A* 算法
 * TypeOfCar  1：无自旋
 *            2：可自旋
 */

std::vector<double> CGraph::AStarForGraph(int Start, int End, int TypeOfCar)
{
    std::vector<int> Path; // 记录块路径
    std::vector<double> Distance(TheMaxNumberOfBlock + 1, 0x3f3f3f3f); // 用距离来保证块尽可能正确
    std::unordered_map<int, int> Close;

    typedef std::pair<double, std::pair<double, int> > PDDI;
    std::priority_queue<PDDI, std::vector<PDDI>, std::greater<PDDI> > Open; // 整体预估值，起点到目前的真实距离，此时点的id

    int StartBlock = Nodes[FindNodeByID(Start)].GetWhichBlock();
    int EndBlock = Nodes[FindNodeByID(End)].GetWhichBlock();
    Open.push({ HForAStar(Blocks[StartBlock].GetX(), Blocks[StartBlock].GetY(), Blocks[EndBlock].GetX(), Blocks[EndBlock].GetY()), {0, StartBlock} });

    Distance[StartBlock] = HForAStar(Blocks[StartBlock].GetX(), Blocks[StartBlock].GetY(), Blocks[EndBlock].GetX(), Blocks[EndBlock].GetY());
    Close[StartBlock] = -1;

    while (!Open.empty())
    {
        PDDI Now = Open.top();
        Open.pop();

        if (Now.second.second == EndBlock) // 如果走到了终点所在的块就路径回溯
        {
            int Back = Now.second.second;
            while (Close[Back] != -1)
            {
                Path.push_back(Back);
                Back = Close[Back];
            }
            Path.push_back(Back);
            reverse(Path.begin(), Path.end());
            break;
        }

        int BeginIndex = FindTheFirstIndexOfTheBlockNeighbor(Now.second.second);
        int EndIndex = FindTheLastIndexOfTheBlockNeighbor(Now.second.second);
        for (int i = BeginIndex; i <= EndIndex; ++i)
        {
            int Last = Bridges[i].GetEndBlockID();
            if (Last == Close[Now.second.second]) // 如果下一个点是这个点来时的路径或者已经走过就无须再走
            {
                continue;
            }

            /*
                整体估值：起始块到目前块 + 目前块到下一个块 + 下一个块到终点块
            */

            double DistanceOfPreviousToNow = HForAStar(Blocks[Last].GetX(), Blocks[Last].GetY(), Blocks[Now.second.second].GetX(), Blocks[Now.second.second].GetY()) * FindBridgeByID(Now.second.second, Last).GetMultiple();
            double DistanceOfNowToLast = HForAStar(Blocks[Now.second.second].GetX(), Blocks[Now.second.second].GetY(), Blocks[EndBlock].GetX(), Blocks[EndBlock].GetY());

            if (Now.second.first + DistanceOfPreviousToNow + DistanceOfNowToLast >= Distance[Last])
            {
                continue;
            }
            Close[Last] = Now.second.second; // 记录 Last 是由此时的点走来的，以便最后进行路径回溯
            Open.push({ Now.second.first + DistanceOfPreviousToNow + DistanceOfNowToLast, {Now.second.first + DistanceOfPreviousToNow, Last} });
            Distance[Last] = Now.second.first + DistanceOfPreviousToNow + DistanceOfNowToLast;
        }
    }

    std::vector<double> Result;
    CNode StartNode = Nodes[FindNodeByID(Start)];
    CNode EndNode;

    for (int i = 0; i < Path.size(); i++) // 根据块的路径一段一段去求真实路径
    {
        if (i + 1 != Path.size()) // 如果此时不是终点块就以块的中心点作为本次 A* 的终点（搜到第一个和中心点在同一个块就停止，并将此点返回作为下一次搜索的起点）
        {
            CNode Temp;
            Temp.SetX(Blocks[Path[i + 1]].GetX());
            Temp.SetY(Blocks[Path[i + 1]].GetY());
            Temp.SetWhichBlock(Path[i + 1]);
            EndNode = Temp;
        }
        else // 如果是终点的块就直接选择对着终点去搜即可
        {
            EndNode = Nodes[FindNodeByID(End)];
        }

        CNode Next = AStarForBlock(StartNode, EndNode, EndNode.GetWhichBlock(), EndBlock, TypeOfCar, Result); // 返回下一次搜索的起点

        if (Next.GetID() == -1)
        {
            break;
        }

        StartNode = Next;
    }

    if (Result.back() != Nodes[FindNodeByID(End)].GetID())
    {
        std::cout << "Dijkstra" << std::endl;

        Result.clear();
        Dijkstra(Start, End, TypeOfCar, Result);
    }

    /**
     * 将 TotalTime 作为 Result 的最后一个元素传递回去
     */

    double TotalTime = 0; // 记录此路径的总时间
    for (int i = 1; i < Result.size(); i++) // 根据求得的路径，一段一段的计算时间（路程 -> GetSize(), 时间 -> 此段道路的最高限速）
    {
        CSegment segment = FindSegmentByID((int)Result[i - 1], (int)Result[i]);
        if (segment.GetIsReverseEdge() == 0)
        {
            if (segment.GetDirection() == 0)
            {
                TotalTime += segment.GetSize() / segment.GetVelocityLimit1();
            }
            else
            {
                TotalTime += segment.GetSize() / 2.5 / segment.GetVelocityLimit2();
            }
        }
        else if (segment.GetIsReverseEdge() == 1)
        {
            if (segment.GetDirection() == 0)
            {
                TotalTime += segment.GetSize() / 2.5 / segment.GetVelocityLimit2(); // 对于反向边长度是加倍的，所以求时间的时候需要先求得真实距离
            }
            else
            {
                TotalTime += segment.GetSize() / segment.GetVelocityLimit1();
            }
        }
    }
    Result.push_back(TotalTime);

    return Result;
}

void CGraph::DebugOfSegments()
{
    for (int i = 0; i < Segments.size(); ++i)
    {
        std::cout << Segments[i].GetID() << ' ' << Segments[i].GetType() << ' '
            << Segments[i].GetWayType() << ' ' << Segments[i].GetStartNodeID() << ' '
            << Segments[i].GetEndNodeID() << ' ' << Segments[i].GetVelocityLimit1() << ' '
            << Segments[i].GetVelocityLimit2() << ' ' << Segments[i].GetDeadReckonDis() << ' '
            << Segments[i].GetObstacle() << ' ' << Segments[i].GetGuideType() << ' '
            << Segments[i].GetDirection() << ' ' << Segments[i].GetSize() << std::endl;
        if (Segments[i].GetType() == 1)
        {
            std::cout << Segments[i].GetSlantAngle() << ' ' << Segments[i].GetFlexible() << ' ';
        }
        else if (Segments[i].GetType() == 3)
        {
            std::cout << Segments[i].GetArcDirection() << ' ' << Segments[i].GetCentralX() << ' ' << Segments[i].GetCentralY() << ' '
                << Segments[i].GetRadius() << ' ' << Segments[i].GetStartAngle() << ' ' << Segments[i].GetEndAngle() << ' ';
        }
        else if (Segments[i].GetType() == 4)
        {
            std::cout << Segments[i].GetStartHeading() << ' ';
        }
        std::cout << Segments[i].GetIsReverseEdge() << std::endl;
    }
}

/**
 * 输出点信息
 */

void CGraph::DebugOfNodes()
{
    for (int i = 0; i < Nodes.size(); ++i)
    {
        std::cout << Nodes[i].GetID() << ' '
            << Nodes[i].GetNodeType() << ' '
            << Nodes[i].GetX() << ' '
            << Nodes[i].GetY() << ' '
            << Nodes[i].GetHeading() << ' '
            << Nodes[i].GetObstacle() << ' '
            << Nodes[i].GetCheckMarkDistance() << ' '
            << Nodes[i].GetCheckMarkVelocity() << ' '
            << Nodes[i].GetRFID() << ' '
            << Nodes[i].GetWhichBlock() << std::endl;
    }
}

/**
 * 输出块信息
 */

void CGraph::DebugOfBlocks()
{
    for (int i = 0; i < Blocks.size(); ++i)
    {
        std::cout << Blocks[i].GetID() << ' '
            << Blocks[i].GetX() << ' '
            << Blocks[i].GetY() << ' '
            << Blocks[i].GetCount() << std::endl;
    }
}

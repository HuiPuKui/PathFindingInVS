#include "Graph.h"

/**
 * ���캯����ʼ��
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
    //Ѱ��n�ڵ����ӽڵ���Ϊnodename�Ľڵ�
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
 * ���� XML �ļ�
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

                // Բ������߳���Ҫ����˳ʱ�롢��ʱ�����ж����Ż������ӻ�

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
            else if (Temp.GetType() == 4) // S �����ߣ�����ʹ��ŷ����þ������
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
 * ���� MakeBlock �ļ�
 */

void CGraph::ParsingFileCalledMakeBlock()
{
    for (int i = 0; i <= TheMaxNumberOfBlock; ++i) // �ڽ����ļ�֮ǰ�ȳ�ʼ����
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
        // �ļ��ڵĸ�ʽ�� X:Y  X��Ϊ���ID��Y��Ϊ���� X �ĵ��ID
        int Index = (int)str.find(":"); // �ҵ� ":" �ָ���
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
        if (StartNode.GetWhichBlock() != EndNode.GetWhichBlock()) // ֻ�������ߵ������˵�ֱ����ڲ�ͬ�Ŀ�ʱ���ſ���Ϊ��ͼ�ӱ�
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
 * ͨ�� ID �ҵ�
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
 * ͨ�� ID ���߶�
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
 * ͨ�� ID ����
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
 * ������ͼ���ڱߣ�����
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
 * ������ͼ���ڱߣ����ң�
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
 * �����ҿ���ڱߣ�����
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
 * �����ҿ���ڱߣ����ң�
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
 * ��ֵ���� ���������پ���
 */

double CGraph::HForAStar(double xl, double yl, double xr, double yr)
{
    double DeltaX = fabs(xl - xr);
    double DeltaY = fabs(yl - yr);
    return DeltaX + DeltaY;
}

/**
 * �� Start --- End -> �ķ���
 */

double CGraph::GetSegmentDirection1(int Start, int End)
{
    CSegment NowSegment = FindSegmentByID(Start, End);
    if (NowSegment.GetIsReverseEdge() == 1)
    {
        NowSegment.SwapNodes();
    }

    double NowDirection = 0;
    if (NowSegment.GetType() == 1 || NowSegment.GetType() == 4) // ֱ��
    {
        NowDirection = NowSegment.GetSlantAngle();
        // ���� �� End To Start �� ���� �� Start To End
        if ((Start == NowSegment.GetStartNodeID() && NowSegment.GetDirection() == 1) || (Start == NowSegment.GetEndNodeID() && NowSegment.GetDirection() == 0))
        {
            NowDirection += 180;
        }
    }
    else if (NowSegment.GetType() == 3) // Բ��
    {
        if (Start == NowSegment.GetStartNodeID()) // ����
        {
            NowDirection = NowSegment.GetEndAngle();
            NowDirection += NowSegment.GetArcDirection() == 0 ? 90 : 270;
        }
        else if (Start == NowSegment.GetEndNodeID()) // ����
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
 * �� -> Start ------ End �ķ���
 */

double CGraph::GetSegmentDirection2(int Start, int End)
{
    CSegment NowSegment = FindSegmentByID(Start, End);
    if (NowSegment.GetIsReverseEdge() == 1)
    {
        NowSegment.SwapNodes();
    }

    double NowDirection = 0;
    if (NowSegment.GetType() == 1 || NowSegment.GetType() == 4) // ֱ��
    {
        NowDirection = NowSegment.GetSlantAngle();
        // ���� �� End To Start �� ���� �� Start To End
        if ((Start == NowSegment.GetStartNodeID() && NowSegment.GetDirection() == 1) || (Start == NowSegment.GetEndNodeID() && NowSegment.GetDirection() == 0))
        {
            NowDirection += 180;
        }
    }
    else if (NowSegment.GetType() == 3) // Բ��
    {
        if (Start == NowSegment.GetStartNodeID()) // ����
        {
            NowDirection = NowSegment.GetStartAngle();
            NowDirection += NowSegment.GetArcDirection() == 0 ? 90 : 270;
        }
        else if (Start == NowSegment.GetEndNodeID()) // ����
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
 * ��С���Ƿ���Դ� Previous --->--- Now �ߵ� Now --->--- Next ������ �������Ƿ���ͬ��
 */

bool CGraph::CheckSegment(int Previous, int Now, int Next)
{
    double PreviousDirection = GetSegmentDirection1(Previous, Now);
    double NextDirection = GetSegmentDirection2(Now, Next);
    double Answer = (double)fabs(PreviousDirection - NextDirection);
    return (double)Answer < 0.1 || (double)fabs(360 - Answer) < 0.1 || (double)fabs(180 - Answer) < 0.1;
}

/**
 * ���·���� A* �㷨����ʼ�㣬��ֹ�㣬��һ���ؾ����ID���յ���ID���ܷ����������ؽ�������ã�
 */

CNode CGraph::AStarForBlock(CNode Start, CNode End, int NextBlockNumber, int EndBlockNumber, int TypeOfCar, std::vector<double>& Result)
{
    std::unordered_map<double, double> Close; // ��¼���е����һ��ĳ���ǶȵĽڵ���ʲô

    int StartNode = Start.GetID();
    int StartBlock = Nodes[FindNodeByID(StartNode)].GetWhichBlock();

    typedef std::pair<double, std::pair<double, double> > PDDD;
    std::priority_queue<PDDD, std::vector<PDDD>, std::greater<PDDD> > Open; // ����Ԥ��ֵ����㵽Ŀǰ����ʵ���룬��ʱ���id

    Open.push({ HForAStar(Start.GetX(), Start.GetY(), End.GetX(), End.GetY()), {0, StartNode * 1000 * 1.0} });

    while (!Open.empty())
    {
        PDDD Now = Open.top();
        Open.pop();

        //std::cout << "From:" << Now.second.second << ' ' << Now.second.first << std::endl;

        int NodeID = (int)(Now.second.second / 1000);
        if ((StartBlock == EndBlockNumber && NodeID == End.GetID()) || (StartBlock != EndBlockNumber && Nodes[FindNodeByID(NodeID)].GetWhichBlock() == NextBlockNumber)) // ���Ŀǰ�������յ㴦��ͬһ����Ļ�
        {
            double Back = Now.second.second;
            int ResultSize = Result.size();
            while (Close.count(Back) && Close[Back] != -1)
            {
                Result.push_back((int)Back / 1000);
                Back = Close[Back];
            }
            if (ResultSize == 0 || (ResultSize && Result[ResultSize - 1] != Back / 1000)) // �жϴ�ʱ�ĵ����һ����������νӵ�ʱ��᲻���ظ�
            {
                Result.push_back((int)Back / (int)1000);
            }
            reverse(Result.begin() + ResultSize, Result.end());
            return Nodes[FindNodeByID(NodeID)];
        }

        if (Nodes[FindNodeByID(NodeID)].GetWhichBlock() != StartBlock) // �����������ʱ���ܳ��������Ͷϵ�
        {
            continue;
        }

        int BeginIndex = FindTheFirstIndexOfTheEdgeNeighbor(NodeID);
        int EndIndex = FindTheLastIndexOfTheEdgeNeighbor(NodeID);

        for (int i = BeginIndex; i <= EndIndex; ++i)
        {
            int Last = Segments[i].GetEndNodeID();
            double Direction = GetSegmentDirection2(Last, NodeID); // ���� X -> Y -> Z �ҵ� X -> Y ������
            double Direction2 = GetSegmentDirection2(NodeID, Last); // ���� X -> Y -> Z �ҵ� Y -> Z ������
            if (Close.count(Last * 1000 * 1.0 + Direction)) // �����ʱ�����������߹��Ͳ���������
            {
                continue;
            }
            if (TypeOfCar == 1 && NodeID != Start.GetID() && CheckSegment((int)Close[Now.second.second] / 1000, NodeID, Last) == false) // ��������޷������Ҳ��ǵ�һ���㣨��Ϊ��һ����û�������ĵ㣬û���ж��������ʣ��������ʲ�ͬ
            {
                continue;
            }

            //std::cout << "To:" << Last << ' ' << Now.second.first << ' ' << Segments[i].GetSize() << std::endl;

            Close[Last * 1000 * 1.0 + Direction] = Now.second.second;
            // ��ֹ��ѭ�����������/�����߹����Ͳ��ܷ�/�������ˣ����߻���·����ʱ��������������ѭ��
            if (!Close.count(NodeID * 1000 * 1.0 + Direction2))
            {
                Close[NodeID * 1000 * 1.0 + Direction2] = -1;
            }
            // Ԥ��ֵ����㵽�˵����ʵ���� + �㵽��һ�������ʵ���� + ��һ���㵽�յ�Ĺ�ֵ����ʵֵ����㵽�˵����ʵ���� + �㵽��һ�������ʵ���룬ID����һ����� ID
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
    std::vector<bool> IsVisited(Nodes.size() + 1, false); // �Ƿ񱻷���
    std::vector<double> Distance(Nodes.size() + 1, 0x3f3f3f3f); // ·������

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
            if (TypeOfCar == 1 && Now.second != Start && CheckSegment(AllPath[Now.second], Now.second, Segments[i].GetEndNodeID()) == false) // ��������޷������Ҳ��ǵ�һ���㣨��Ϊ��һ����û�������ĵ㣬û���ж��������ʣ��������ʲ�ͬ
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
    while (AllPath[Back] != -1) // ·������
    {
        Result.push_back(Back);
        Back = AllPath[Back];
    }
    Result.push_back(Back);
    reverse(Result.begin(), Result.end());
}

/**
 * ������·���� A* �㷨
 * TypeOfCar  1��������
 *            2��������
 */

std::vector<double> CGraph::AStarForGraph(int Start, int End, int TypeOfCar)
{
    std::vector<int> Path; // ��¼��·��
    std::vector<double> Distance(TheMaxNumberOfBlock + 1, 0x3f3f3f3f); // �þ�������֤�龡������ȷ
    std::unordered_map<int, int> Close;

    typedef std::pair<double, std::pair<double, int> > PDDI;
    std::priority_queue<PDDI, std::vector<PDDI>, std::greater<PDDI> > Open; // ����Ԥ��ֵ����㵽Ŀǰ����ʵ���룬��ʱ���id

    int StartBlock = Nodes[FindNodeByID(Start)].GetWhichBlock();
    int EndBlock = Nodes[FindNodeByID(End)].GetWhichBlock();
    Open.push({ HForAStar(Blocks[StartBlock].GetX(), Blocks[StartBlock].GetY(), Blocks[EndBlock].GetX(), Blocks[EndBlock].GetY()), {0, StartBlock} });

    Distance[StartBlock] = HForAStar(Blocks[StartBlock].GetX(), Blocks[StartBlock].GetY(), Blocks[EndBlock].GetX(), Blocks[EndBlock].GetY());
    Close[StartBlock] = -1;

    while (!Open.empty())
    {
        PDDI Now = Open.top();
        Open.pop();

        if (Now.second.second == EndBlock) // ����ߵ����յ����ڵĿ��·������
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
            if (Last == Close[Now.second.second]) // �����һ�������������ʱ��·�������Ѿ��߹�����������
            {
                continue;
            }

            /*
                �����ֵ����ʼ�鵽Ŀǰ�� + Ŀǰ�鵽��һ���� + ��һ���鵽�յ��
            */

            double DistanceOfPreviousToNow = HForAStar(Blocks[Last].GetX(), Blocks[Last].GetY(), Blocks[Now.second.second].GetX(), Blocks[Now.second.second].GetY()) * FindBridgeByID(Now.second.second, Last).GetMultiple();
            double DistanceOfNowToLast = HForAStar(Blocks[Now.second.second].GetX(), Blocks[Now.second.second].GetY(), Blocks[EndBlock].GetX(), Blocks[EndBlock].GetY());

            if (Now.second.first + DistanceOfPreviousToNow + DistanceOfNowToLast >= Distance[Last])
            {
                continue;
            }
            Close[Last] = Now.second.second; // ��¼ Last ���ɴ�ʱ�ĵ������ģ��Ա�������·������
            Open.push({ Now.second.first + DistanceOfPreviousToNow + DistanceOfNowToLast, {Now.second.first + DistanceOfPreviousToNow, Last} });
            Distance[Last] = Now.second.first + DistanceOfPreviousToNow + DistanceOfNowToLast;
        }
    }

    std::vector<double> Result;
    CNode StartNode = Nodes[FindNodeByID(Start)];
    CNode EndNode;

    for (int i = 0; i < Path.size(); i++) // ���ݿ��·��һ��һ��ȥ����ʵ·��
    {
        if (i + 1 != Path.size()) // �����ʱ�����յ����Կ�����ĵ���Ϊ���� A* ���յ㣨�ѵ���һ�������ĵ���ͬһ�����ֹͣ�������˵㷵����Ϊ��һ����������㣩
        {
            CNode Temp;
            Temp.SetX(Blocks[Path[i + 1]].GetX());
            Temp.SetY(Blocks[Path[i + 1]].GetY());
            Temp.SetWhichBlock(Path[i + 1]);
            EndNode = Temp;
        }
        else // ������յ�Ŀ��ֱ��ѡ������յ�ȥ�Ѽ���
        {
            EndNode = Nodes[FindNodeByID(End)];
        }

        CNode Next = AStarForBlock(StartNode, EndNode, EndNode.GetWhichBlock(), EndBlock, TypeOfCar, Result); // ������һ�����������

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
     * �� TotalTime ��Ϊ Result �����һ��Ԫ�ش��ݻ�ȥ
     */

    double TotalTime = 0; // ��¼��·������ʱ��
    for (int i = 1; i < Result.size(); i++) // ������õ�·����һ��һ�εļ���ʱ�䣨·�� -> GetSize(), ʱ�� -> �˶ε�·��������٣�
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
                TotalTime += segment.GetSize() / 2.5 / segment.GetVelocityLimit2(); // ���ڷ���߳����Ǽӱ��ģ�������ʱ���ʱ����Ҫ�������ʵ����
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
 * �������Ϣ
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
 * �������Ϣ
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

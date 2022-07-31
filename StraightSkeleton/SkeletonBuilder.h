#pragma once
#include <vector>
#include <unordered_set>
#include <queue>
#include <memory>
#include <algorithm>
#include "Skeleton.h"
#include "Vertex.h"
#include "Edge.h"
#include "CircularList.h"
#include "MultiEdgeEvent.h"
#include "PickEvent.h"
#include "MultiSplitEvent.h"
#include "SplitEvent.h"
#include "FaceQueueUtil.h"
#include "PrimitiveUtils.h"

/// <summary> 
///     Straight skeleton algorithm implementation. Base on highly modified Petr
///     Felkel and Stepan Obdrzalek algorithm. 
/// </summary>
/// <remarks> 
///     This is a C++ adopted port of java implementation from kendzi-straight-skeleton library.
/// </remarks>
class SkeletonBuilder
{	
	
protected:
	/// <summary>
	///     Check if given point is on one of edge bisectors. If so this is vertex
	///     split event. This event need two opposite edges to process but second
	///     (next) edge can be take from edges list and it is next edge on list.
	/// </summary>
	/// <param name="point">Point of event.</param>
	/// <param name="edge">candidate for opposite edge.</param>
	/// <returns>previous opposite edge if it is vertex split event.</returns>
	static Edge VertexOpositeEdge(Vector2d point, Edge edge);
private:
	struct SplitCandidate
	{
	public:
		double Distance;
		Edge OppositeEdge;
		Vector2d OppositePoint;
		Vector2d Point;

		SplitCandidate(Vector2d point, double distance, Edge oppositeEdge, Vector2d oppositePoint)
		{
			Point = point;
			Distance = distance;
			OppositeEdge = oppositeEdge;
			OppositePoint = oppositePoint;
		}
	};
	// Error epsilon.
	const double SplitEpsilon = 1E-10;
	static std::vector<Vector2d> InitPolygon(std::vector<Vector2d>& polygon);	
	static void ProcessTwoNodeLavs(std::unordered_set<Vertex,CircularList> sLav);
	static void RemoveEmptyLav(std::unordered_set<CircularList> sLav);
	static void MultiEdgeEvent(MultiEdgeEvent event, std::priority_queue<SkeletonEvent> queue, std::vector<Edge> edges);
	static void AddMultiBackFaces(std::vector<EdgeEvent> edgeList, Vertex edgeVertex);
	static void PickEvent(PickEvent event);
	static void MultiSplitEvent(MultiSplitEvent event, std::unordered_set<Vertex,CircularList> sLav, std::priority_queue<SkeletonEvent> queue, std::vector<Edge> edges);
	static void CorrectBisectorDirection(LineParametric2d bisector, Vertex beginNextVertex, Vertex endPreviousVertex, Edge beginEdge, Edge endEdge);
	static FaceNode AddSplitFaces(FaceNode lastFaceNode, IChain chainBegin, IChain chainEnd, Vertex newVertex);
	static Vertex CreateOppositeEdgeVertex(Vertex newVertex);
	static void CreateOppositeEdgeChains(std::unordered_set<Vertex,CircularList> sLav, std::vector<IChain> chains, Vector2d center);
	static Vertex CreateMultiSplitVertex(Edge nextEdge, Edge previousEdge, Vector2d center, double distance);
	/// <summary>
	///     Create chains of events from cluster. Cluster is set of events which meet
	///     in the same result point. Try to connect all event which share the same
	///     vertex into chain. events in chain are sorted. If events don't share
	///     vertex, returned chains contains only one event.
	/// </summary>
	/// <param name="cluster">Set of event which meet in the same result point</param>
	/// <returns>chains of events</returns>
	static std::vector<IChain> CreateChains(std::vector<SkeletonEvent> cluster);
	static bool IsInEdgeChain(SplitEvent split, EdgeChain chain);
	static std::vector<EdgeEvent> CreateEdgeChain(std::vector<EdgeEvent> edgeCluster);
	static void RemoveEventsUnderHeight(std::priority_queue<SkeletonEvent> queue, double levelHeight);
	static std::vector<SkeletonEvent> LoadAndGroupLevelEvents(std::priority_queue<SkeletonEvent> queue);
	static std::vector<SkeletonEvent> GroupLevelEvents(std::vector<SkeletonEvent> levelEvents);
	static bool IsEventInGroup(std::unordered_set<Vertex> parentGroup, SkeletonEvent event);
	static void AddEventToGroup(std::unordered_set<Vertex> parentGroup, SkeletonEvent event);
	static SkeletonEvent CreateLevelEvent(Vector2d eventCenter, double distance, std::vector<SkeletonEvent> eventCluster);
	/// <summary> Loads all not obsolete event which are on one level. As level heigh is taken epsilon. </summary>
	static std::vector<SkeletonEvent> LoadLevelEvents(std::priority_queue<SkeletonEvent> queue);
	static int AssertMaxNumberOfInteraction(int count);
	static std::vector<std::vector<Vector2d>>& MakeClockwise(std::vector<std::vector<Vector2d>>& holes);
	static std::vector<Vector2d> MakeCounterClockwise(std::vector<Vector2d>& polygon);
	static void InitSlav(std::vector<Vector2d>& polygon, std::unordered_set<std::shared_ptr<CircularList>, CircularList::HashFunction>& sLav, std::vector<Edge*>& edges, std::vector<FaceQueue*>& faces);
	static Skeleton AddFacesToOutput(std::vector<FaceQueue> faces);
	static void InitEvents(std::unordered_set<Vertex,CircularList> sLav, std::priority_queue<SkeletonEvent> queue, std::vector<Edge> edges);
	static void ComputeSplitEvents(Vertex vertex, std::vector<Edge> edges, std::priority_queue<SkeletonEvent> queue, double distanceSquared);
	static void ComputeEvents(Vertex vertex, std::priority_queue<SkeletonEvent> queue, std::vector<Edge> edges);
	/// <summary>
	///     Calculate two new edge events for given vertex. events are generated
	///     using current, previous and next vertex in current lav. When two edge
	///     events are generated distance from source is check. To queue is added
	///     only closer event or both if they have the same distance.
	/// </summary>
	static double ComputeCloserEdgeEvent(Vertex vertex, std::priority_queue<SkeletonEvent> queue);
	static SkeletonEvent CreateEdgeEvent(Vector2d point, Vertex previousVertex, Vertex nextVertex);
	static void ComputeEdgeEvents(Vertex previousVertex, Vertex nextVertex, std::priority_queue<SkeletonEvent> queue);
	static std::vector<SplitCandidate> CalcOppositeEdges(Vertex vertex, std::vector<Edge> edges);
	static bool EdgeBehindBisector(LineParametric2d bisector, LineLinear2d edge);
	static SplitCandidate CalcCandidatePointForSplit(Vertex vertex, Edge edge);
	static Edge ChoseLessParallelVertexEdge(Vertex vertex, Edge edge);
	static Vector2d ComputeIntersectionBisectors(Vertex vertexPrevious, Vertex vertexNext);
	static Vertex FindOppositeEdgeLav(std::unordered_set<Vertex,CircularList> sLav, Edge oppositeEdge, Vector2d center);
	static Vertex ChooseOppositeEdgeLav(std::vector<Vertex> edgeLavs, Edge oppositeEdge, Vector2d center);
	static std::vector<Vertex> FindEdgeLavs(std::unordered_set<Vertex,CircularList> sLav, Edge oppositeEdge, CircularList skippedLav);
	
	/// <summary>
		///     Take next lav vertex _AFTER_ given edge, find vertex is always on RIGHT
		///     site of edge.
		/// </summary>
	static Vertex* GetEdgeInLav(CircularList& lav, Edge& oppositeEdge);
	static void AddFaceBack(Vertex* newVertex, Vertex* va, Vertex* vb);
	static void AddFaceRight(Vertex* newVertex, Vertex vb);
	static void AddFaceLeft(Vertex* newVertex, Vertex va);
	static double CalcDistance(Vector2d intersect, Edge currentEdge);
	static Vector2d CalcVectorBisector(Vector2d norm1, Vector2d norm2);
	static LineParametric2d CalcBisector(Vector2d* p, Edge e1, Edge e2);
	template<typename T>
	size_t hash(const std::shared_ptr<T>& ptr)
	{
		return ((size_t)ptr.get()) / sizeof(T);
	}
	template<typename T>
	bool equal_to(const std::shared_ptr<T>& left, const std::shared_ptr<T>& right)
	{
		return left.get() == right.get();
	}
	/*
	class SkeletonEventDistanseComparer : IComparer<SkeletonEvent>
	{
		public int Compare(SkeletonEvent left, SkeletonEvent right)
		{
			return left.Distance.CompareTo(right.Distance);
		}
	};
	class ChainComparer : IComparer<IChain>
	{
		private readonly Vector2d _center;

		public ChainComparer(Vector2d center)
		{
			_center = center;
		}

		public int Compare(IChain x, IChain y)
		{
			if (x == y)
				return 0;

			var angle1 = Angle(_center, x.PreviousEdge.Begin);
			var angle2 = Angle(_center, y.PreviousEdge.Begin);

			return angle1 > angle2 ? 1 : -1;
		}

		private static double Angle(Vector2d p0, Vector2d p1)
		{
			var dx = p1.X - p0.X;
			var dy = p1.Y - p0.Y;
			return Math.Atan2(dy, dx);
		}
	}
	class SplitCandidateComparer : IComparer<SplitCandidate>
	{
		public int Compare(SplitCandidate left, SplitCandidate right)
		{
			return left.Distance.CompareTo(right.Distance);
		}
	}
	*/
	
public:
	
	/// <summary> Creates straight skeleton for given polygon. </summary>
	static Skeleton Build(std::vector<Vector2d>& polygon);
	/// <summary> Creates straight skeleton for given polygon with holes. </summary>
	static Skeleton Build(std::vector<Vector2d>& polygon, std::vector<std::vector<Vector2d>>& holes);
	
};

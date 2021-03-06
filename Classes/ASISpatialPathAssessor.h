//
//  ASISpatialPathAssessor.h
//  Part of ASIPathFinder --> http://allseeing-i.com/ASIPathFinder
//
//  Created by Ben Copsey on 20/03/2009.
//  Copyright 2009 All-Seeing Interactive. All rights reserved.
//
//  ASISpatialPathAssessor is a class that implements an A* path finder - it looks for a full route between two points
//  When used in conjunction with an ASISpaceTimePathFinder, it acts as the first stage to finding a path
//  Tell the path assessor to search backwards from the destination to the origin, and it will record the distance of each point on the way from the destination
//  The space time path finder can then use this data to figure out where to go next without having to compute a full path each time

#import "ASIPathSearchDataTypes.h"

@class ASIWorldMap;
@class ASIMapObject;
@class ASIPath;
@class ASIUnit;
@class ASISearchNodeList;

@interface ASISpatialPathAssessor : NSObject {
	
	// The starting point - when used with a space time path finder, this will normally be the destination position
	Position3D origin;
	
	// The end point - when used with a space time path finder, this will normally be the starting position
	Position3D destination;
	
	
	// A reference to the map - we look here to find fixed objects (eg buildings) that are in the way
	ASIWorldMap *map;
	
	// An array of positions we've looked at - the distance from our origin position will be stored here
	float *positions;
	
	// Our list of nodes waiting to be assessed - these are ordered in such a way that the best node to consider next is always the first one
	ASISearchNodeList *nodeList;
	
	// The object that wants to assess a path - we use this to ensure an object will ignore itself when looking for free positions
	ASIUnit *object;
	
	// Set to YES when we fail to find a route between two positions
	BOOL failedToFindRoute;
	
	// Set to YES when path assessment is complete
	// Will be NO if the maximum number of nodes have been searched - calling resumeSearch will continue from where we left off
	BOOL haveFinishedAssessingPath;
	
	// When set to YES, we are resuming a path search because we have had to move off course, and have not assessed nodes nearby
	// When this happens, as soon as we find a space we've already assessed, we stop path finding, since this will allow us to get back on course
	BOOL shouldPerformOffCourseAssessment;
}

// Create a new path assessor
- (id)initWithMap:(ASIWorldMap *)newMap;

// Clear the path assessment
// Allows us to start path assessment again
// Use this rather than creating a new path assessor every time a unit wants to find a new path to avoid the overhead of allocating and freeing storage every time
- (void)reset;

// Attempt to find a path between two points
// Rather than returning a path, we record the distance from our origin of each point along the way
// A space time path finder can then use this data as a hint for where to go next as it plans
- (void)assessPathFrom:(Position3D)newOrigin to:(Position3D)newDestination;

// Space time path finders use this to obtain the distance from their destination of a particular position they are considering
- (float)realDistanceFromDestination:(Position3D)position;
- (BOOL)haveAssessed:(Position3D)position;

// Resume a paused search
- (void)resumeSearch;

@property (assign, nonatomic) Position3D origin;
@property (assign, nonatomic) Position3D destination;
@property (assign, nonatomic) ASIWorldMap *map;
@property (assign, nonatomic) ASIUnit *object;
@property (assign, nonatomic) BOOL failedToFindRoute;
@property (assign, nonatomic) BOOL haveFinishedAssessingPath;
@property (retain, nonatomic) ASISearchNodeList *nodeList;
@property (assign, nonatomic) BOOL shouldPerformOffCourseAssessment;
@end

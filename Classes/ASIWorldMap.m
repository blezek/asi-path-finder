//
//  ASIWorldMap.m
//  Part of ASIPathFinder --> http://allseeing-i.com/ASIPathFinder
//
//  Created by Ben Copsey on 28/02/2010.
//  Copyright 2010 All-Seeing Interactive. All rights reserved.
//

#import "ASIWorldMap.h"
#import "MapObject.h"
#import "ASISpaceTimeMap.h"
#import "ASIMoveableObject.h"

@implementation ASIWorldMap

+ (id)map
{
    return [[[ASIWorldMap alloc] initWithMapSize:Size3DMake(20, 20, 1)] autorelease];
}

- (id)initWithMapSize:(Size3D)newSize
{
	self = [super initWithMapSize:newSize];
	[self setObjects:[NSMutableArray array]];
	[self setSpaceTimeMap:[[[ASISpaceTimeMap alloc] initWithSize:CGSizeMake(20, 20) timeSpan:20] autorelease]];
	return self;
}

- (void)addObject:(MapObject *)object
{
	[objects addObject:object];
	[super setObject:object atPosition:[object position]];
}

- (void)removeObject:(MapObject *)object
{
	[super removeObject:object atPosition:[object position]];
	[objects removeObject:object];
}

- (void)removeObjectAtPosition:(Position3D)position
{
	MapObject *object = [self objectAtPosition:position];
	if (object) {
		[self removeObject:object];
	}
}

- (NSArray *)moveableObjects
{
	NSMutableArray *units = [NSMutableArray array];
	for (MapObject *object in objects) {
		if ([object isKindOfClass:[ASIMoveableObject class]]) {
			[units addObject:object];
		}
	}
	return units;
}


@synthesize objects;
@synthesize spaceTimeMap;
@end

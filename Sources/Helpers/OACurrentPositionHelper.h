//
//  OACurrentPositionHelper.h
//  OsmAnd
//
//  Created by Alexey Kulish on 08/10/2017.
//  Copyright © 2017 OsmAnd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

#include <OsmAndCore/Data/Road.h>

@class OAMapRendererView;

@interface OACurrentPositionHelper : NSObject

+ (OACurrentPositionHelper *)instance;

+ (double) getOrthogonalDistance:(std::shared_ptr<const OsmAnd::Road>) r loc:(CLLocation *)loc;
- (std::shared_ptr<const OsmAnd::Road>) getLastKnownRouteSegment:(CLLocation *)loc;
- (void) clearCacheNotInTiles:(OAMapRendererView *)mapRendererView;

@end

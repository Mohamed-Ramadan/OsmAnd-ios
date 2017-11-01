//
//  OAMapViewController.h
//  OsmAnd
//
//  Created by Alexey Pelykh on 7/18/13.
//  Copyright (c) 2013 OsmAnd. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "OACommonTypes.h"
#import "OAMapRendererViewProtocol.h"
#import "OAObservable.h"
#import <Reachability.h>
#import "OAAppSettings.h"
#import "OAPOIType.h"

#define kNotificationSetTargetPoint @"kNotificationSetTargetPoint"
#define kNotificationNoSymbolFound @"kNotificationNoSymbolFound"
#define kNotificationMapGestureAction @"kNotificationMapGestureAction"
#define kNotificationContextMarkerClicked @"kNotificationContextMarkerClicked"
#define kNotificationLayersConfigurationChanged @"kNotificationLayersConfigurationChanged"

#define kCorrectionMinLeftSpace 40.0
#define kCorrectionMinBottomSpace 40.0
#define kCorrectionMinLeftSpaceBBox 20.0
#define kCorrectionMinBottomSpaceBBox 20.0

#if defined(OSMAND_IOS_DEV)
typedef NS_ENUM(NSInteger, OAVisualMetricsMode)
{
    OAVisualMetricsModeOff = 0,
    OAVisualMetricsModeBinaryMapData,
    OAVisualMetricsModeBinaryMapPrimitives,
    OAVisualMetricsModeBinaryMapRasterize
};
#endif // defined(OSMAND_IOS_DEV)

typedef NS_ENUM(NSInteger, OAMapSymbolType)
{
    OAMapSymbolUndefined = 0,
    OAMapSymbolContext,
    OAMapSymbolMyLocation,
    OAMapSymbolDestination,
    OAMapSymbolFavorite,
    OAMapSymbolWiki,
    OAMapSymbolWpt,
    OAMapSymbolPOI,
    OAMapSymbolLocation,
    OAMapSymbolTurn,
};

@class OAGpxWpt;
@class OAGpxMetadata;
@class OAGPXRouteDocument;
@class OAPOIUIFilter;
@class OASearchWptAPI;
@class OAMapRendererView;

@interface OAMapSymbol : NSObject

@property (nonatomic) int symbolId;
@property (nonatomic) unsigned long long obfId;
@property (nonatomic) CLLocationCoordinate2D location;
@property (nonatomic) CGPoint touchPoint;
@property (nonatomic) OAPOIType *poiType;
@property (nonatomic) UIImage *icon;
@property (nonatomic) NSString *caption;
@property (nonatomic) NSString *captionExt;
@property (nonatomic) NSString *buildingNumber;
@property (nonatomic) OAMapSymbolType type;
@property (nonatomic) NSInteger sortIndex;

@property (nonatomic) NSDictionary *values;

@property (nonatomic) BOOL isPlace;
@property (nonatomic) BOOL centerMap;
@property (nonatomic) BOOL minimized;

@property (nonatomic) NSDictionary *localizedNames;
@property (nonatomic) NSDictionary *localizedContent;

@property (nonatomic) OAGpxWpt *foundWpt;
@property (nonatomic) NSArray *foundWptGroups;
@property (nonatomic) NSString *foundWptDocPath;

@property (nonatomic) NSString* symbolGroupId;

@end


@interface OAMapViewController : UIViewController <UIGestureRecognizerDelegate>

@property(nonatomic, readonly) OAMapRendererView* mapView;
@property(weak, readonly) id<OAMapRendererViewProtocol> mapRendererView;
@property(readonly) OAObservable* stateObservable;
@property(readonly) OAObservable* settingsObservable;

@property(readonly) OAObservable* azimuthObservable;
- (void)animatedAlignAzimuthToNorth;

@property(readonly) OAObservable* zoomObservable;
@property(readonly) OAObservable* mapObservable;

@property (nonatomic) OAGpxWpt *foundWpt;
@property (nonatomic) NSArray *foundWptGroups;
@property (nonatomic) NSString *foundWptDocPath;

- (CLLocation *) getMapLocation;
- (float) getMapZoom;

- (void)setDocFileRoute:(NSString *)fileName;
- (void)setGeoInfoDocsGpxRoute:(OAGPXRouteDocument *)doc;

- (BOOL)hasFavoriteAt:(CLLocationCoordinate2D)location;
- (BOOL)hasWptAt:(CLLocationCoordinate2D)location;

- (BOOL)findWpt:(CLLocationCoordinate2D)location;
- (BOOL)deleteFoundWpt;
- (BOOL)saveFoundWpt;
- (BOOL)addNewWpt:(OAGpxWpt *)wpt gpxFileName:(NSString *)gpxFileName;

- (BOOL)canZoomIn;
- (void)animatedZoomIn;
- (BOOL)canZoomOut;
- (void)animatedZoomOut;

- (void)goToPosition:(Point31)position31
            animated:(BOOL)animated;
- (void)goToPosition:(Point31)position31
             andZoom:(CGFloat)zoom
            animated:(BOOL)animated;

- (void)correctPosition:(Point31)targetPosition31
       originalCenter31:(Point31)originalCenter31
              leftInset:(CGFloat)leftInset
            bottomInset:(CGFloat)bottomInset
             centerBBox:(BOOL)centerBBox
               animated:(BOOL)animated;

- (float)calculateMapRuler;

- (BOOL)isMyLocationVisible;

- (void)showContextPinMarker:(double)latitude longitude:(double)longitude animated:(BOOL)animated;
- (void)hideContextPinMarker;

- (BOOL)simulateContextMenuPress:(UIGestureRecognizer*)recognizer;

- (void)showRouteGpxTrack;
- (void)hideRouteGpxTrack;

- (void)showTempGpxTrack:(NSString *)fileName;
- (void)hideTempGpxTrack;
- (void)keepTempGpxTrackVisible;

- (void)showRecGpxTrack;
- (void)hideRecGpxTrack;

- (void)showPoiOnMap:(NSString *)category type:(NSString *)type filter:(NSString *)filter keyword:(NSString *)keyword;
- (void)showPoiOnMap:(OAPOIUIFilter *)uiFilter keyword:(NSString *)keyword;
- (void)hidePoi;

- (BOOL)deleteWpts:(NSArray *)items docPath:(NSString *)docPath;
- (BOOL)updateWpts:(NSArray *)items docPath:(NSString *)docPath updateMap:(BOOL)updateMap;
- (BOOL)updateMetadata:(OAGpxMetadata *)metadata docPath:(NSString *)docPath;

- (void)setWptData:(OASearchWptAPI *)wptApi;

- (void)runWithRenderSync:(void (^)(void))runnable;
- (void)updateLayer:(NSString *)layerId;

+ (void)postTargetNotification:(NSArray<OAMapSymbol *> *)symbolArray latitude:(double)latitude longitude:(double)longitude;
+ (void)postTargetNotification:(OAMapSymbol *)symbol;
+ (OAMapSymbol *)getMapSymbol:(OAPOI *)poi;

@property(readonly) CGFloat displayDensityFactor;

@property(readonly) OAObservable* framePreparedObservable;
@property(readonly) OAObservable* frameDisplayedObservable;
@property(readonly) OAObservable* idleObservable;

@property(nonatomic, assign) BOOL minimap;

#if defined(OSMAND_IOS_DEV)
@property(nonatomic) BOOL hideStaticSymbols;
@property(nonatomic) OAVisualMetricsMode visualMetricsMode;

@property(nonatomic) BOOL forceDisplayDensityFactor;
@property(nonatomic) CGFloat forcedDisplayDensityFactor;
#endif // defined(OSMAND_IOS_DEV)

- (void) fireWaitForIdleEvent;

@end

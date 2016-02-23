//
//  IntripperMap.h
//  Intripper
//
//  Created by Sanginfo on 20/01/16.
//  Copyright © 2016 Sanginfo. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import "IndoorMapObject.h"
#import "PathFormatter.h"
#import "TrackingMarker.h"
/**
 *  Navigation Modes
 */
typedef NS_ENUM(NSInteger, NavigationMode) {
    /**
     *  Non-Navigation mode
     */
    NavigationMode_None,
    /**
     *  Navigation Preview mode
     */
    NavigationMode_Preview,
    /**
     * Navigation with turn by turn instructions mode.
     */
    NavigationMode_TurnByTurn
};
/**
 *  Description
 *
 *  @param formatter <#formatter description#>
 *
 *  @return <#return value description#>
 */
typedef PathFormatter* (^PathFormatterBlock)(PathFormatter *formatter);
/**
 *  Delegates for the events on Intripper object.
 */
@protocol IntripperMapDelegate<NSObject>

@optional
-(void)IndoorMapLoaded:(id)sender;
/**
 *  Called after a long-press gesture at a particular coordinate.
 *
 *  @param mapView    The mapview that was pressed.
 *  @param coordinate The location that was pressed.
 *  @param level      The current level/floor on the mapview where the long-press gesture was triggered.
 */
-(void)intripper:(id)mapView didLongPressAtCoordinate:(CLLocationCoordinate2D)coordinate floor:(int)level;
/**
 *  Called after a tap gesture at a particular coordinate
 *
 *  @param mapView    The mapview that was tapped.
 *  @param coordinate The location that was tapped.
 *  @param level      The current level/floor on the mapview where the tap gesture was triggered.
 */
-(void)intripper:(id)mapView didTapAtCoordinate:(CLLocationCoordinate2D)coordinate floor:(int)level;
/**
 *  Called after the user location is found in a geo-fenced promo zone.
 *
 *  @param mapView The mapview where the user location is found.
 *  @param Zone    A dictionary of the geo-fenced zone.
 *  @param offers  An array of offers found in the geo-fenced promo zone.
 */
-(void)intripper:(id)mapView enterPromoZone:(NSDictionary *)Zone promotion:(NSArray *)offers;
/**
 *  Called after the user exits from a previously enteres geo-fenced promo zone.
 *
 *  @param mapView The mapview where the user location is found.
 *  @param Zone    A dictionary of the geo-fenced zone from where the user made an exit from.
 */
-(void)intripper:(id)mapView exitPromoZone:(NSDictionary *)Zone;
/**
 *  Called after the application desires to display route between two points.
 *
 *  @param mapView   The mapview where the route will be drawn.
 *  @param routeList An array of geojson objects 
 */
-(void)intripper:(id)mapView Route:(NSArray *)routeList;
-(void)intripper:(id)mapView NoRoute:(NSArray *)routeList;
/**
 *  Called when user wants turn by turn instructions.
 *
 *  @param mapView   The mapview where the route for turn by turn is drawn.
 *  @param pathIndex The index of the area/section.
 *  @param routeInfo The area/section data
 */
-(void)intripper:(id)mapView Instruction:(NSUInteger)pathIndex pathInfo:(NSDictionary *)routeInfo;
/**
 *  Called when user moves away from the route that is drawn. It is called when user is in navigation mode.
 *
 *  @param mapView    The mapview that caused the event to trigger.
 *  @param coordinate The current coordinates of the position user.
 *  @param level      The level at which the user is currently present.
 */
-(void)intripper:(id)mapView ReRouteWithLocation:(CLLocationCoordinate2D)coordinate floor:(int)level;


-(void)intripper:(id)mapView NavigationInterrupted:(BOOL)coordinate;

/**
 *  Called when change in floor is detected.
 *
 *  @param mapView The mapview that caused the event to trigger.
 *  @param level   The level of the floor change.
 */
-(void)intripper:(id)mapView FloorChange:(int)level;
/**
 *  Called after a double tap gesture is detected on floor selector.
 *
 *  @param mapView The map view where the double tap was detected
 *  @param level The level selected by the user.
 */
-(void)intripper:(id)mapView FloorTapRepeat:(int)level;
/**
 *  Floor list of map
 *
 *  @param mapView The mapview that caused the event to trigger.
 *  @param levels The NSArray of levels for the venue.
 */
-(void)intripper:(id)mapView ActiveFloorList:(NSArray *)levels;

/**
 *  Called when the user location is detected in a geo-fenced area for elevators/escalators indicating
 *  probable floor change action.
 *
 *  @param mapView mapView The mapview where the user location is found.
 *  @param region  region A dictionary of the elevator/escalator found nearby the user's location.
 */
-(void)intripper:(id)mapView enterFloorChangeRegion:(NSDictionary *)region;
/**
 *  Called when the user moves out of the geo-fenced region for elevators/escalators.
 *
 *  @param mapView mapView The mapview where the user location is found.
 *  @param region  region A dictionary of the elevator/escalator from where the user has exited.
 */
-(void)intripper:(id)mapView exitFloorChangeRegion:(NSDictionary *)region;


/**
 *  Called when the user arrives at destination in navigation mode.
 *
 *  @param mapView The mapview
 *  @param navigationState YES if user is arriving near the destination.
 */
-(void)intripper:(id)mapView endNavigation:(BOOL)navigationState;

/**
 *  Called when a marker is about to become selected, and provides an optional
 *  custom info window to use for that marker if this method returns a UIView.
 *
 *  @param mapView mapView The mapview where the marker window will be shown.
 *  @param title   title The text to show on the marker window.
 *
 *  @return The custom info window for the specified marker, or nil for default
 */
-(UIView *)intripper:(id )mapView markerInfoWindow:(NSString *)title;
/**
 *  Called when a tap gesture is detected on the marker's info window.
 *
 *  @param mapView The mapview where the marker is shown.
 *  @param markerDetail The marker's user data.
 */
- (void) intripper:(id )mapView didTapInfoWindowOfMarker:(NSDictionary *)markerDetail;

-(void)SetBlueDotOnLongPress:(double)latitude longitude:(double)longitude;
@end
/**
 *  This is the main class of InTripper SDK for IOS and is the entry point for all the methods related to map.
 *  The map should be instantiated via the convenience constructor [[IntripperMap alloc] init]
 
 */
@interface IntripperMap : UIViewController{
}
//Properties
/**
 *  Sets the VenueID for the map.
 */
    @property (nonatomic,retain) NSString *VenueID;
/**
 *  Sets the default floor to be shown when the map loads.
 */
    @property (nonatomic,readwrite) int floorNumber;
/**
 *  Controls whether the map uses custom tiles (Default renderer for Custom Tiles is MapBox) 
 *  or it uses Google Maps.
 */
    @property (nonatomic,readwrite) BOOL useMapboxMap;
/**
 *  Controls whether user can abandon navigation during navigation mode.
 */

    @property (nonatomic,readwrite) BOOL allowUserToInterruptNavigation;
/**
 *  Gets the current Navigation mode.
 */
    @property (nonatomic,readonly,  getter = getCurrentMapMode) NavigationMode CurrentMapMode;
/**
 *  IntripperMapDelegate delegate
 */
    @property(nonatomic,weak) id <IntripperMapDelegate> mapdelegate;
/**
 *  S Navigation  path
 */
   @property (copy) PathFormatterBlock pathOptions;
/**
 *  Controls whether the mapview's inbuilt floor selector to be show. Set NO if the application wants to create custom floor selector.
 */
    @property (nonatomic,readwrite) BOOL enableFloorSelector;
/**
 *  Sets the navigation mode.
 *
 *  @param mode Navigation mode type (NavigationMode_None,NavigationMode_Preview,NavigationMode_TurnByTurn)
 */
-(void)setNavigationMode:(NavigationMode)mode;
/**
 *  Gets the current Navigation Mode
 *
 *  @return Enumumeraton of type NavigationMode
 */
-(NavigationMode)getCurrentMapMode;
//Methods
    -(void)autoFit;
//Markers
/**
 *  Displays a marker on the mapview.
 *
 *  @param coordinate Location
 *  @param level      Floor Level
 *  @param Title      Title to display on the marker window
 */
    -(void)showMarker:(CLLocationCoordinate2D)coordinate floor:(int)level title:(NSString *)Title;
//User Location
/**
 *  Sets the user's current position(blue dot) on map.
 *
 *  @param latitude  Latitude
 *  @param longitude Longitude
 */
    -(void)setBlueDot:(double)latitude longitude:(double)longitude;
/**
 *  Sets the user's current position(blue dot) on map.
 *
 *  @param location The location of the user's current position.
 *  @param level    The floor level of the user's current position.
 */
    -(void)setBlueDot:(CLLocation *)location onFloor:(int)level;
/**
 *  Gets the user's current location.
 *
 *  @return The latitude, longitude and floor level of the user's position.
 */
    -(CGIndoorMapPoint)userLocation;
/**
 *  Returns the information of the tapped area on map.
 *
 *  @param location Location that was tapped.
 *  @param level    floor level.
 *
 *  @return Returns a dictionary of the the tapped area.
 */
    -(NSDictionary *) getTappedAreaInfo :(CLLocation *)location onFloor:(int)level;
/**
 *  Centers the blue dot in the map view.
 */
    -(void)centerBlueDot;
    
//Routing
/**
 *  Finds the path from source to destination.
 *
 *  @param startPoint Source Coordinates
 *  @param endPoint   Destination Coordinates
 */
    -(void)FindRoute:(CGIndoorMapPoint)startPoint destination:(CGIndoorMapPoint)endPoint;
/**
 *  Finds the path from source to destination with an option to end the path at the source area entrance or the path should end inside of the store. Useful when user wants to draw a path uptil a store entrance or to a POI located inside the store.
 *
 *  @param startPoint     Source Coordinates
 *  @param endPoint       Destination Coordinates
 *  @param cutAtEnterance BOOL flag
 */
    -(void)FindRoute:(CGIndoorMapPoint)startPoint destination:(CGIndoorMapPoint)endPoint uptoDoor:(BOOL)cutAtEnterance;
/**
 *  Ends the navigation when user's navigation mode is NavigationMode_TurnByTurn
 */
    -(void)exitNavigation;
/**
 *  Called when allowUserToInterruptNavigation is set to TRUE
 */
    -(void)resumeNavigation;
//Instruction
/**
 *  Sets the corresponding instruction for navigation for the selected index.
 *
 *  @param instructionIndex The index for getting the instruction.
 */
    -(void)StepToInstruction:(NSInteger)instructionIndex;
/**
 *  Sets the corresponding instruction for the next step. 
    The user's navigation mode should be NavigationMode_TurnByTurn.
    Useful when user wants to scoll through a set of instructions.
 */
    -(void)NextStepInstruction;
/**
 *  Sets the corresponding instruction for navigation for the previous step.
    The user's navigation mode should be NavigationMode_TurnByTurn.
    Useful when user wants to scoll through a set of instructions.
 */
    -(void)PreviousStepInstruction;
//Re-Route New Path
    -(void)ReRoute:(CLLocationCoordinate2D)coordinate floor:(int)level;

/**
 *  Suppress reroute event For 5 seconds
 */
-(void)suppressReRouteEvent;
//Floor Bar Methods
/**
 *  Changes the floor for the mapview.
 *
 *  @param floor The floor to be set.
 */
    - (void) changeFloor:(int) floor;
/**
 *  Removes current markers from the mapview.
 */
-(void)mapCleanup;
//Mark Store on map
/**
 *  Finds a area/section on the map and displays a corresponding marker on the mapview.
 *
 *  @param coordinate The location of the area/section to find.
 *  @param level      The level at which the area/secton is located.
 */
-(void)FindAreaOnMap:(CLLocationCoordinate2D)coordinate floor:(int)level;
//Mark Poi on map
/**
 *  Finds an area (typically used to find a POI) and displays a corresponding marker on the mapview.
 *
 *  @param coordinate The location of the area(POI) to find.
 *  @param level      The level at which the area(POI) is located.
 *  @param text       The title of the area(POI) that will be dsplayed on the marker window.
 */
-(void)FindAreaOnMap:(CLLocationCoordinate2D)coordinate floor:(int)level title:(NSString *)text;
/**
 *  Finds a area/section on the map and displays a corresponding marker on the mapview.
 *
 *  @param storeid The unique ID of the area/section to find.
 */
-(void)FindAreaOnMap:(NSString *)storeid;

//Indoor Positioning Services
/**
 *  Gets the indoor positioning service's unique floor plan ID for the selected floor/level.
 *
 *  @param floor The floor for which the unique floor plan ID is returned
 *
 *  @return Returns the a unique floor plan ID.
 */
    -(NSString *) LocationFloorRef:(int) floor;
/**
 *  Gets the API key for the indoor positioning services.
 *
 *  @return The API key for the indoor positioning services.
 */
    -(NSString *)IAAPIapikey;
/**
 *  Gets the API secret for the indoor positioning services.
 *
 *  @return The API secret for the indoor positioning services.
 */
    -(NSString *)IAAPIapiSecret;
/**
 *  Returns an array of unique floor plan IDs of the indoor positioning services.
 *
 *  @return NSArray of floor plan IDs
 */
    -(NSArray *)LocationFloorRefID;

//Tracking
/**
 *  Adds a marker for buddy on the map.
 *
 *  @param tracking An instance of the class <<TrackingMarker>>
 */
-(void)addTrackingMarker:(TrackingMarker *)tracking;
/**
 *  Updates the maker position of the buddy at specific intervals.
 *
 *  @param coordinate The current position of the buddy.
 *  @param level      The level at which the buddy is present.
 */
-(void)UpdateTrackingMarker:(CLLocationCoordinate2D)coordinate floor:(int)level;
/**
 *  Removes the buddy marker
 */
-(void)RemoveTrackingMarker;
//Map Information
/**
 *  Gets the store data available for a particular venue.
 *
 *  @return NSArray of stores.
 */
-(NSArray *)AllStoreInformation;
@end

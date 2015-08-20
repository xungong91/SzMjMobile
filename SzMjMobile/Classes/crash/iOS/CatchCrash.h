//
//  NSObject+CatchCrash.h
//  SzMjMobile
//
//  Created by gongxun on 15/8/18.
//
//

#import <Foundation/Foundation.h>

@interface CatchCrash : NSObject

volatile void uncaughtExceptionHandler(NSException *exception);

extern NSUncaughtExceptionHandler *exceptionHandlerPtr;

@end

//
//  NSObject+CatchCrash.m
//  SzMjMobile
//
//  Created by gongxun on 15/8/18.
//
//

#import "CatchCrash.h"

@implementation CatchCrash : NSObject

volatile void uncaughtExceptionHandler(NSException *exception)
{
    // 异常的堆栈信息
    NSArray *stackArray = [exception callStackSymbols];
    
    // 出现异常的原因
    NSString *reason = [exception reason];
    
    // 异常名称
    NSString *name = [exception name];
    
    // 异常时间
    NSDate * senddate = [NSDate date];
    NSDateFormatter *dateformatter=[[NSDateFormatter alloc] init];
    [dateformatter setDateFormat:@"YYYY-MM-dd HH:mm:ss"];
    NSString *date = [dateformatter stringFromDate:senddate];
    
    //设备型号
    NSString *model = [[UIDevice currentDevice] model];
    
    //系统版本号
    NSString *systemVersion = [[UIDevice currentDevice] systemVersion];
    
    //app版本号
    NSString *app_Version = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    
    //异常msg
    NSString *exceptionInfo = [NSString stringWithFormat:
                               @"Exception date：%@ \nException modelName：%@ \nException systemVersion：%@ \nException app_Version：%@ \nException reason：%@\nException name：%@\nException stack：%@",
                               date,
                               model,
                               systemVersion,
                               app_Version,
                               name,
                               reason,
                               stackArray];
    
//    NSLog(@"%@", exceptionInfo);
    
    NSMutableArray *tmpArr = [NSMutableArray arrayWithArray:stackArray];
    
    [tmpArr insertObject:reason atIndex:0];
    
    //保存到本地
    [exceptionInfo writeToFile:[NSString stringWithFormat:@"%@/Documents/error.log",NSHomeDirectory()]  atomically:YES encoding:NSUTF8StringEncoding error:nil];
}

NSUncaughtExceptionHandler *exceptionHandlerPtr = &uncaughtExceptionHandler;

@end

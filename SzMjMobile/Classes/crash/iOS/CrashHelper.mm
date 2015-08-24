
//
//  CrashHelper.m
//  SzMjMobile
//
//  Created by gongxun on 15/8/17.
//
//

#import <Foundation/Foundation.h>
#include "CrashHelper.h"
#include "CatchCrash.h"

static int s_fatal_signals[] = {
    SIGABRT,
    SIGBUS,
    SIGFPE,
    SIGILL,
    SIGSEGV,
    SIGTRAP,
    SIGTERM,
    SIGKILL,
};

static const char* s_fatal_signal_names[] = {
    "SIGABRT",
    "SIGBUS",
    "SIGFPE",
    "SIGILL",
    "SIGSEGV",
    "SIGTRAP",
    "SIGTERM",
    "SIGKILL",
};

static int s_fatal_signal_num = sizeof(s_fatal_signals) / sizeof(s_fatal_signals[0]);

void signalHandler(int signal) {
    for (int i = 0; i <s_fatal_signal_num; ++i) {
        if (signal == s_fatal_signals[i]) {
            NSLog(@"exit with signal: %s", s_fatal_signal_names[i]);
//            NSLog(@"%@", [AppDelegate backtrace]);
            break;
        }
    }
}

void CrashHelper::InitCrashReport()
{
    NSString *file = [NSString stringWithFormat:@"%@/Documents/error.log",NSHomeDirectory()];
    NSLog(@"错误文件%@", file);
    
    //如果文件存在 就上传到服务器
    handlError();
    
    // 1     linux错误信号捕获
    for (int i = 0; i < s_fatal_signal_num; ++i) {
        signal(s_fatal_signals[i], signalHandler);
    }
    
    // 2      objective-c未捕获异常的捕获
    NSSetUncaughtExceptionHandler(exceptionHandlerPtr);
}

void CrashHelper::throwError()
{
    //
    
    //数组越界
    [[NSArray array] objectAtIndex:1];
}






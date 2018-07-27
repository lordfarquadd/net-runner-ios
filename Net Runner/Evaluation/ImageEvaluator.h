//
//  ImageEvaluator.h
//  tflite_camera_example
//
//  Created by Philip Dow on 7/18/18.
//  Copyright © 2018 doc.ai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "Evaluator.h"
#import "VisionModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface ImageEvaluator : NSObject <Evaluator>

@property (readonly) UIImage *image;
@property (readonly) id<VisionModel> model;
@property (readonly) NSDictionary *results;

- (instancetype)initWithImage:(UIImage*)image model:(id<VisionModel>)model;

- (void)evaluateWithCompletionHandler:(nullable EvaluatorCompletionBlock)completionHandler;

@end

NS_ASSUME_NONNULL_END

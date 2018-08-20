//
//  TIOModelJSONParsing.h
//  Net Runner
//
//  Created by Philip Dow on 8/20/18.
//  Copyright © 2018 doc.ai. All rights reserved.
//

#import <Foundation/Foundation.h>

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>

#import "TIOData.h"
#import "TIODataInterface.h"
#import "Quantization.h"
#import "VisionModelHelpers.h"

@class TIOModelBundle;
@class TIODataInterface;

NS_ASSUME_NONNULL_BEGIN

/**
 * Parses the JSON description of a vector input or output.
 *
 * Handles a vector, matrix, or other multidimensional array (tensor), described as a
 * one dimensional unrolled vector with an optional labels entry.
 *
 * @param dict The JSON description in `NSDictionary` format
 * @param isInput `YES` if this is an input layer, `NO` if it is an output layer
 * @param quantized `YES` if the layer expects or returns quantized bytes, `NO` otherwise
 * @param bundle `The ModelBundel` that is being parsed, needed to derive a path to the labels file
 *
 * @return TIODataInterface An interface that describes this pixel buffer input or output
 */

TIODataInterface * _Nullable TIOTFLiteModelParseTIOVectorDescription(NSDictionary *dict, BOOL isInput, BOOL quantized, TIOModelBundle *bundle);

/**
 * Parses the JSON description of a pixel buffer input or output.
 *
 * Pixel buffers are handled as their own case instead of as a three-dimensional volume because
 * of byte alignment and pixel format conversion requirements.
 *
 * @param dict The JSON description in `NSDictionary` format
 * @param isInput `YES` if this is an input layer, `NO` if it is an output layer
 * @param quantized `YES` if the layer expects or returns quantized bytes, `NO` otherwise
 *
 * @return TIODataInterface An interface that describes this pixel buffer input or output
 */

TIODataInterface * _Nullable TIOTFLiteModelParseTIOPixelBufferDescription(NSDictionary *dict, BOOL isInput, BOOL quantized);

/**
 * Parses the `quantization` key of an input description and returns an associated data quantizer
 */

_Nullable DataQuantizer TIODataQuantizerForDict(NSDictionary *dict);

/**
 * Parses the `dequantization` key of an output description and returns an associated data quantizer
 */

_Nullable DataDequantizer TIODataDequantizerForDict(NSDictionary *dict);

/**
 * Converts an array of shape values to an `ImageVolume`.
 */

ImageVolume ImageVolumeForShape(NSArray<NSNumber*> *shape);

/**
 * Converts a pixel format string such as `"RGB"` or `"BGR"` to a Core Video pixel format type.
 */

OSType PixelFormatForString(NSString* formatString);

/**
 * Returns the PixelNormalization given an input dictionary.
 */

PixelNormalization PixelNormalizationForDictionary(NSDictionary *input);

/**
 * Returns the PixelNormalizer given an input dictionary.
 */

PixelNormalizer _Nullable PixelNormalizerForDictionary(NSDictionary *input);

/**
 * Returns the denormalizing PixelNormalization given an input dictionary
 */

PixelDenormalization PixelDenormalizationForDictionary(NSDictionary *input);

/**
 * Returns the denormalizer for a given input dictionary
 */

PixelDenormalizer _Nullable PixelDenormalizerForDictionary(NSDictionary *input);

// MARK: - Pixel Format

/**
 * No pixel format, used to represent an error reading the pixel format from the model.json file.
 */

extern const OSType PixelFormatTypeInvalid;

// MARK: - Assets

/**
 * Reads the labels associated with a TIOVector feature.
 */

void LoadLabels(NSString* labels_path, std::vector<std::string>* label_strings);

NS_ASSUME_NONNULL_END
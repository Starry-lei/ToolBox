//
// Created by cheng on 14.11.22.
//

#ifndef PHOTOMETRICLOSS_PFMREADWRITE_H
#define PHOTOMETRICLOSS_PFMREADWRITE_H




/*
 *     PFM_ReadWrite
 *
 *     Author:  Antoine TOISOUL LE CANN
 *
 *     Copyright © 2016 Antoine TOISOUL LE CANN, Imperial College London
 *              All rights reserved
 *
 *
 * PFM_ReadWrite is free software: you can redistribute it and/or modify
 *
 * it under the terms of the GNU Lesser General Public License as published by
 *
 * the Free Software Foundation, either version 3 of the License, or
 *
 * (at your option) any later version.
 *
 * PFM_ReadWrite is distributed in the hope that it will be useful,
 *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file PFMReadWrite.h
 * \brief Implementation of loadPFM and savePFM functions.
 * \author Antoine Toisoul Le Cann
 * \date September, 1st, 2016
 *
 * Implementation of loadPFM and savePFM functions.
 */


#include <iostream>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv/highgui.h>

/**
 * Loads a PFM image stored in little endian and returns the image as an OpenCV Mat.
 * @brief loadPFM
 * @param filePath
 * @return
 */
cv::Mat loadPFM(const std::string filePath);

/**
 * Saves the image as a PFM file.
 * @brief savePFM
 * @param image
 * @param filePath
 * @return
 */
bool savePFM(const cv::Mat image, const std::string filePath);



#endif //PHOTOMETRICLOSS_PFMREADWRITE_H

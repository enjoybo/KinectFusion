//
// Created by pbo on 08.07.19.
//

#pragma once

#include "Volume.hpp"
#include <Frame.h>
#include <memory>
class Fusion {
public:
//THIS method expects frame to hold all camera paramerters as well as the estimated pose --> TODO: check if those values are set or redefine method parameters

    bool reconstructSurface(std::shared_ptr<Frame> currentFrame,std::shared_ptr<Volume> volume,double truncationDistance);

private:

    void reconstruct(std::shared_ptr<Frame> currentFrame,std::shared_ptr<Volume> volume,float truncationDistance);
    //Reconstruction
    bool calculateGlobal2CameraPoint(Eigen::Vector3d &currentCameraPosition, int x, int y, int z,
									 Eigen::Matrix<double, 3, 3, Eigen::DontAlign> rotation,
									 Eigen::Vector3d translation, double voxelScale);

    bool pi(Eigen::Vector2i& unhomogenized,Eigen::Vector3d homogenized, Eigen::Matrix3d intrinsics,int width, int height);

        /*!
         * The original implementation actually takes a raw depth Value, as we already calculated the camereSpacePoints
         * only the normalization has to be done.
         * TODO: move normalization to frame.cpp ; check if the cameraSpaceTransformation in frame.cpp equals the one used in Paper
         * @param cameraSpacePoint
         * @return the normalized cameraSpaceCoordinates
         */
    double calculateLamdas(Eigen::Vector2i& cameraSpacePoint,Eigen::Matrix3d intrinsics);
    /*!
     *
     * @param lambda
     * @param cameraPosition
     * @param rawDepthValue
     * @return the signed-distance-function for the specific depth value lambda is based on
     */

    double calculateSDF(double& lambda,Eigen::Vector3d& cameraPosition,double rawDepthValue);

};



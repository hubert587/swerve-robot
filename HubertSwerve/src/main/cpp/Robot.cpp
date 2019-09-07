/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include <cameraserver/CameraServer.h>
#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <subsystems/Lift.h>
#include <subsystems/Beak.h>

#include <thread>


#include <iostream>
#include <cameraserver/CameraServer.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <wpi/raw_ostream.h>
#include <DigitalInput.h>


//ExampleSubsystem Robot::m_subsystem;
OI Robot::m_oi;
SwerveDrive Robot::m_drivetrain;
Lift Robot::m_lift;
Beak Robot::m_beak;

void Robot::VisionThread() {

  frc::DigitalInput InZero{0};
  frc::DigitalInput InOne{1};
  frc::DigitalInput InTwo{2};

    // Get the USB camera from CameraServer
    cs::UsbCamera camera =
        frc::CameraServer::GetInstance()->StartAutomaticCapture();
    // Set the resolution
    camera.SetResolution(320, 240);

    // Get a CvSink. This will capture Mats from the Camera
    cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo();
    // Setup a CvSource. This will send images back to the Dashboard
    cs::CvSource outputStream =
        frc::CameraServer::GetInstance()->PutVideo("Rectangle", 640, 480);

    // Mats are very memory expensive. Lets reuse this Mat.
    cv::Mat mat;

    while (true) {
      // Tell the CvSink to grab a frame from the camera and
      // put it
      // in the source mat.  If there is an error notify the
      // output.
      if (cvSink.GrabFrame(mat) == 0) {
        // Send the output the error.
        outputStream.NotifyError(cvSink.GetError());
        // skip the rest of the current iteration
        continue;
      }

      

      int Data = 0;
      if (InZero.Get()){

        Data++;

      } 
      
      if (InOne.Get()){

        Data = Data + 2;

      } 
      
      if (InTwo.Get()){

        Data = Data + 4;

      }

      std::cout << InZero.Get() << InOne.Get() << InTwo.Get() << "\n"; 

       if (Data == 0) {

        //Does Nothing

      } else if (Data == 1) {

        //Very Far Left
        arrowedLine(mat, cv::Point(400, 200), cv::Point(550, 200), cv::Scalar(255, 0, 0), 5, 1, 1, 0.5);


      } else if (Data == 2){

       //Far Left
       arrowedLine(mat, cv::Point(400, 200), cv::Point(500, 200), cv::Scalar(255, 0, 0), 5, 1, 1, 0.5);

      } else if (Data == 3) {

       //Near Left
      arrowedLine(mat, cv::Point(400, 200), cv::Point(450, 200), cv::Scalar(255, 0, 0), 5, 1, 1, 0.5);

      } else if (Data == 4) {
      // Put a rectangle on the image
      //Center
      rectangle(mat, cv::Point(100, 100), cv::Point(200, 200),
                cv::Scalar(0, 255, 0), 5);
      // Give the output stream a new image to display
      } else if (Data == 5) {

        //Near Right
        arrowedLine(mat, cv::Point(150, 200), cv::Point(100, 200), cv::Scalar(0, 0, 255), 5, 0, 1, 0.5);

      } else if (Data == 6){

        //Far Right
        arrowedLine(mat, cv::Point(200, 200), cv::Point(100, 200), cv::Scalar(0, 0, 255), 5, 0, 1, 0.5);


      } else if (Data == 7){
        
        //Very Far Right
        arrowedLine(mat, cv::Point(250, 200), cv::Point(100, 200), cv::Scalar(0, 0, 255), 5, 0, 1, 0.5);


      }outputStream.PutFrame(mat);
    }
  }


void Robot::RobotInit() {
  //m_chooser.SetDefaultOption("Default Auto", &m_defaultAuto);
 // m_chooser.AddOption("My Auto", &m_myAuto);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  //frc::SmartDashboard::PutString("DB/String 0", "3.54");
	//std::string strLeftFront = frc::SmartDashboard::GetString("DB/String 0", "");

  //std::thread visionThread(VisionThread);
  //visionThread.detach();
  m_drivetrain.enable();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {
  // std::string autoSelected = frc::SmartDashboard::GetString(
  //     "Auto Selector", "Default");
  // if (autoSelected == "My Auto") {
  //   m_autonomousCommand = &m_myAuto;
  // } else {
  //   m_autonomousCommand = &m_defaultAuto;
  // }

  m_autonomousCommand = m_chooser.GetSelected();

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Start();
  }
}

void Robot::AutonomousPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
}

void Robot::TeleopPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif

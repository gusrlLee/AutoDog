
- Central Processing System
    - threads
        - Camera Capture thread 
            - DogStatus  
            - camrea 

        - LiDAR scan data thread 
            - DogStatus  
            - LiDAR 

        - Compute Visual odometry Trajectory
            - visual odometry 
            - DogStatus  

        - Display Monitor Thread
            - Display 
            - DogStatus  
            
        - Motor Control Thread
            - Legs 
            - DogStatus  

    - Camera
        - Camera Pose
        - Frame Processer 
    
    - Visual Odometry
        - K matrix (focal length, center_point) 

    - LiDAR
        - Driver 
        - LiDAR Scan Data 
        - rotaion $\theta$

    - Legs
        - moters of arduino control
        - Serial comunicate between Jetson Nano and Arduino

    - DogStatus  
        - All of Main System information 
        - Current Frame
        - Current Trajectory
        - Current Lidar Scan Data 
        - Current status
        - all of previous information 

    - Display
      - GUI 
      - input control
      - 2 Viewer (current frame, Trajectory frame)
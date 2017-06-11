# Car_Lane_Shifter
  Using a trained classifier and computer vision  techniques, we designed a car lane shifter helper which aids the driver in shifting lanes  safely.

  At first we wanted to detect cars using some color segmentation and ccl but it took time to implement the first trial. The results weren’t good, low detection results. Then we thought about using a trained classifier to help us in detecting the cars so we can start putting some logic to the code. We found a trained classifier, trained on 528 images of different types and sizes of cars. It generated much better detection results, but the problem is that the car had to be faced to the camera while our project deals with the car from the side view. So sometimes detection sometimes would wait until all the width of the car was in the frame processed. However, in general it detected cars. Another issue is that sometimes the classifier would detect some noise in the road and sky as a car, we recognize this problem as the dataset isn’t that big. So we did some result filtering that would remove those errors. For the sky, we remove the all the upper part of the frame which contained the sky, so we solved the sky false detection as a car.  As for the road, we only gave attention to the cars that are beside me or the ones with a close proximity reducing errors coming from the far false cars detection that wouldn’t contribute in the decision on whether to shift lanes or not. Off course lane detection had also to be implemented. We used opencv functions like canny and houghlines to detect the lines and to know on which lane are we relatively to the middle dashed line. Sure thing we removed the noises by Gaussian blur.
  
  As for the project logic, we used a trapezoidal shape to reflect on whether to shift or not. If it was green then it is safe to shift lanes, while if red it isn’t. All the time the lane would say it is safe, unless a car is detected with a close proximity on the lane.


# Screenshots

Trapezoid is red since a car was passing by. Therefore, the driver cannot shift lanes.
![alt tag](https://github.com/yehiahesham/Car_Lane_Shifter/blob/master/sc1.png) 

Car is detected but it is in the same lane and far away from the driver. Therefore the trapezoid is green and the driver can shift lanes.
![alt tag](https://github.com/yehiahesham/Car_Lane_Shifter/blob/master/sc2.png)

Here, there are cars in the other lane, so the driver can't shift.
![alt tag](https://github.com/yehiahesham/Car_Lane_Shifter/blob/master/sc3.png)

Here, a truck is detected in the other lane but it is far away so the driver is still safe to switch lanes.
![alt tag](https://github.com/yehiahesham/Car_Lane_Shifter/blob/master/sc4.png)

# Watchdog
## Inspiration
With the added emphasis of safety on college campuses, there is a clear and 
obvious need to develop a platform to ensure that all students return home 
safe. In this project, we set out just to do so. Human capital is an expensive 
resource for universities, so we created an app which can simulate a companion 
for walking home.

## What it does
Pebble application that prompts the user to 'check-in' after fixed length of 
time or a contact will be notified via SMS.

## How we built it
The code for the pebble was coded and build in the CloudPebble web IDE.  This 
provided a very simple way to code/build/deploy our work on our pebble devices.
Once the web IDE was setup, building and deploying was as easy as clicking a 
button.  However, this IDE proved to be difficult for collaboration.  Since the
code was hosted on the cloud servers, we had no way to use our own source 
control.  This meant that we had to rely on the GitHub integration in 
CloudPebble, which is not designed for multiple developers.

As the pebble app was being built, the companion Android app was being built in
Android Studio.  We found that the integration between pebble and android was 
very seamless.  The packages were easy to include and use in the android app.

## Challenges we ran into
* It was not clear what the capabilities of the pebble for running code on the 
host device
* The suggested cloud IDE did not integrate GitHub very well
  - pulling a repository overwrote all of the changes you had in the project 
  - merging from the IDE was impossible, the commit forced itself to head
* The members of the team did not have experience with pebble

## Accomplishments that we're proud of
* The app works
* The team learned about the pebble platform and what it can do

## What's next for SafeTap
* possible rework of the connection to the phone to allow for launching from 
the phone
* look into the AppSync functionality of pebble and Android
* develop a companion app on iPhone
* the possiblity of geofencing the user

## Developers 
* Colin Heim
* Henry Wrightman
* Matthew Schiffler
* Nikita Yurkov
* Seth Rickard

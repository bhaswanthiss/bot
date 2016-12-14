warning('off','vision:transition:usesOldCoordinates')
clear all
clc
answer=1;
arduino=serial('COM3','BaudRate',9600);
fopen(arduino);
%pointTracker = vision.PointTracker;
faceDetector = vision.CascadeObjectDetector();
obj =imaq.VideoDevice('winvideo', 2, 'RGB24_640x480','ROI', [1 1 640 480]);
set(obj,'ReturnedColorSpace', 'rgb');
figure('menubar','none','tag','webcam');
wait=0;
while (wait<400)
    wait=wait+1;
    frame=step(obj);
    bbox=step(faceDetector,frame);
    wait
    if(~isempty(bbox))
        bbox
        centx=bbox(1) + (bbox(3)/2) ;
        centy=bbox(2) - (bbox(4)/2) ;
        c1=(centx);
        c2=(centy);
        c1
        c2
        fprintf(arduino,'%s',char(centx));      
        fprintf(arduino,'%s',char(centy));
    end
     boxInserter  = vision.ShapeInserter('BorderColor','Custom',...
    'CustomBorderColor',[255 0 255]);
   
videoOut = step(boxInserter, frame,bbox);

    imshow(videoOut,'border','tight');
   
    f=findobj('tag','webcam');
    
    if (isempty(f));
        [hueChannel,~,~] = rgb2hsv(frame);
rectangle('Position',bbox(1,:),'LineWidth',2,'EdgeColor',[1 1 0])

hold off

noseDetector = vision.CascadeObjectDetector('Nose');

faceImage    = imcrop(frame,bbox);

noseBBox     = step(noseDetector,faceImage);

noseBBox(1:1) = noseBBox(1:1) + bbox(1:1);
videoInfo    = info(obj);
ROI=get(obj,'ROI');

VideoSize = [ROI(3) ROI(4)];
videoPlayer  = vision.VideoPlayer('Position',[300 300 VideoSize+60]);

tracker = vision.HistogramBasedTracker;
initializeObject(tracker, hueChannel, bbox);
time=0;
while (time<400)
    time=time+1;
    
    frame = step(obj);
    time

    [hueChannel,~,~] = rgb2hsv(frame);
    
    bbox = step(tracker, hueChannel);
    
    videoOut = step(boxInserter, frame, bbox);
    
    step(videoPlayer, videoOut);
    pause (.2)
end
time
release(obj);
release(videoPlayer);

        close(gcf)
        break
    end
    pause(0.05)
    
end
fclose(arduino);
release(obj);

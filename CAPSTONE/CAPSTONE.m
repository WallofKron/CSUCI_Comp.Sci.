function varargout = CAPSTONE(varargin)
% CAPSTONE MATLAB code for CAPSTONE.fig
%      CAPSTONE, by itself, creates a new CAPSTONE or raises the existing
%      singleton*.
%
%      H = CAPSTONE returns the handle to a new CAPSTONE or the handle to
%      the existing singleton*.
%
%      CAPSTONE('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in CAPSTONE.M with the given input arguments.
%
%      CAPSTONE('Property','Value',...) creates a new CAPSTONE or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before CAPSTONE_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to CAPSTONE_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES
% Edit the above text to modify the response to help CAPSTONE
% Last Modified by GUIDE v2.5 22-Apr-2018 10:32:26
% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @CAPSTONE_OpeningFcn, ...
                   'gui_OutputFcn',  @CAPSTONE_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT
end

% --- Executes just before CAPSTONE is made visible.
function CAPSTONE_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to CAPSTONE (see VARARGIN)

Images='/Users/RobertFlorence/Documents/MATLAB/Images';
a=dir([Images '/*.jpg']);
folderElemList = {a(:).name};

folderElemList = horzcat('select Image', folderElemList);

set(handles.Image_Popup,'string',folderElemList); 
set(handles.Image_Popup,'max',length(folderElemList)); 


% Choose default command line output for CAPSTONE
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes CAPSTONE wait for user response (see UIRESUME)
% uiwait(handles.figure1);
end


% --- Outputs from this function are returned to the command line.
function varargout = CAPSTONE_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Get default command line output from handles structure
varargout{1} = handles.output;
end


% --- Executes on selection change in Image_Popup.
function Image_Popup_Callback(hObject, eventdata, handles)
% hObject    handle to Image_Popup (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
str = get(hObject,'String');
val = get(hObject,'Value');

handles.SelectedImage = str{val};

axes(handles.picOutput1);


if strcmp(handles.SelectedImage, 'select Image')
disp('Select your Image to Segment\n')
else
handles.image = im2double(imread(handles.SelectedImage));
imshow(handles.image);
end

guidata(hObject, handles);

% Hints: contents = cellstr(get(hObject,'String')) returns Image_Popup contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Image_Popup
end



% --- Executes during object creation, after setting all properties.
function Image_Popup_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Image_Popup (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end




% --- Executes on selection change in Algorithm_Popup.
function Algorithm_Popup_Callback(hObject, eventdata, handles)
% hObject    handle to Algorithm_Popup (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
str = get(hObject,'String');
val = get(hObject,'Value');

switch str{val}
    case 'Watershed1'
        handles.SelectedAlgorithm = 'Watershed1';
    case 'Watershed2'
        handles.SelectedAlgorithm = 'Watershed2';
    case 'Mean Shift Clustering'
        handles.SelectedAlgorithm = 'Mean Shift Clustering';
    case 'Region Growing'
        handles.SelectedAlgorithm = 'Region Growing';   
end
guidata(hObject, handles);
% Hints: contents = cellstr(get(hObject,'String')) returns Algorithm_Popup contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Algorithm_Popup
end





% --- Executes during object creation, after setting all properties.
function Algorithm_Popup_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Algorithm_Popup (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

handles.SelectedAlgorithm = 'Watershed1';
guidata(hObject, handles);

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end




% --- Executes on button press in Run_Button.
function Run_Button_Callback(hObject, eventdata, handles)
% hObject    handle to Run_Button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
switch(handles.SelectedAlgorithm)
    case 'Region Growing'
        tic
        baseregionValue = 0.1;
        RegionGrowingTolerance = 0.2;
        regValOffset = 1;
        numregions = 50;
        regVals(numregions,3) = 0;
        [x,y,~] = size(handles.image);
        dataMatrix(x,y,3) = 0;
        axes(handles.picOutput2);
        seedCounter = 0;
        tolerance = 0.15;
        
        imshow(handles.image + dataMatrix);
        guidata(hObject, handles);
        drawnow;
        
        
        for i=1:x
           for k=1:y
               if dataMatrix(i,k,1) == 0
                  seedCounter=seedCounter+1;
                  regionValue = regValOffset * baseregionValue;
                  
                  [J,colorMean] = regiongrowing(handles.image, i, k, RegionGrowingTolerance, regionValue);
                  
                  rlTol = colorMean(1) - (tolerance * colorMean(1));
                  rhTol = colorMean(1) + (tolerance * colorMean(1));
                  glTol = colorMean(2) - (tolerance * colorMean(2));
                  ghTol = colorMean(2) + (tolerance * colorMean(2));
                  blTol = colorMean(3) - (tolerance * colorMean(3));
                  bhTol = colorMean(3) + (tolerance * colorMean(3));
                  
                  
                  for regidx = 1: numregions                %compare generated region to current regions using tolerance values
                    if (regVals(regidx,1) <= rhTol && regVals(regidx,1) >= rlTol) && (regVals(regidx,2) <= ghTol && regVals(regidx,2) >= glTol) && (regVals(regidx,3) <= bhTol && regVals(regidx,3) >= blTol)
                        for z = 1:x
                            for c = 1:y
                                if(J(z,c,1) == regionValue)
                                  J(z,c,1) = regidx * baseregionValue; 
                                end
                            end
                        end
                        break;
                    end
                    if(regVals(regidx,1) == 0.0)&&(regVals(regidx,2) == 0.0)&&(regVals(regidx,3) == 0.0)    %if no regions exist, init one
                        regVals(regidx,1) = colorMean(1);
                        regVals(regidx,2) = colorMean(2);
                        regVals(regidx,3) = colorMean(3);
                        break;
                    end
                  end
                
                  
                  for n=1:x             %copy new J region over to dataMatrix, not over writing other sections
                      for m=1:y
                         if(dataMatrix(n,m,1)==0)
                         dataMatrix(n,m,1)=J(n,m,1);
                         end
                      end
                  end
                  
                  regValOffset = regValOffset + 1;
                  imshow(handles.image + dataMatrix);
                  guidata(hObject, handles);
                  drawnow;
               end
           end
        end
        tempMatrix = dataMatrix;
        tempMatrix(:,:,1) = 10 * tempMatrix(:,:,1);     %convert datamatrix over to integers to color separate regions
        tempMatrix = uint8(tempMatrix);
        
        nzelemRegVals = uint8(nnz(regVals)/3);          %number of regions
        
        area(nzelemRegVals,2) = 0;              % init area 2d array
        
        for g = 1:nzelemRegVals
            countymcCountyface = 0;
            area(g,1) = g;
            for r=1:x
                for s=1:y
                    if (tempMatrix(r,s) == g)
                        countymcCountyface = countymcCountyface + 1;
                    end
                end
            end
            area(g,2) = ((countymcCountyface/(x*y)) * 100);         %calculate the area of said region
        end
        
        for r=1:x
                for s=1:y
                    modVal = mod(tempMatrix(r,s),6);
                    if (modVal == 0)            %red
                    dataMatrix(r,s,1) = 0.3;
                    end
                    
                    if (modVal == 1)             %green
                    dataMatrix(r,s,2) = 0.3;
                    dataMatrix(r,s,1) = 0.0;
                    end
                    
                    if (modVal == 2)            %blue
                    dataMatrix(r,s,3) = 0.3;
                    dataMatrix(r,s,1) = 0.0;
                    end
                    
                    if (modVal == 3)            %teal
                    dataMatrix(r,s,3) = 0.3;
                    dataMatrix(r,s,2) = 0.3;
                    dataMatrix(r,s,1) = 0.0;
                    end
                    
                    if (modVal == 4)             %Purple
                    dataMatrix(r,s,3) = 0.3;
                    dataMatrix(r,s,1) = 0.3;
                    dataMatrix(r,s,2) = 0.0;
                    end
                    
                    if (modVal == 5)             %yellow
                    dataMatrix(r,s,1) = 0.3;
                    dataMatrix(r,s,2) = 0.3;
                    dataMatrix(r,s,3) = 0.0;
                    end
                end
        end
                    
        handles.image = handles.image + dataMatrix;         %make handles.image into segmented image. To save the image.
        imshow(handles.image);
        
        t = uitable(handles.uitable2);
        set(t,'Data',area);                  % Used to change the area uitable properties.
        set(t,'ColumnName',{'region';'area'})
        set(t,'Visible','on');
        
        guidata(hObject, handles);
        drawnow;
        disp("Finito!")
        toc
        
        
        
    case 'Watershed1'
        tic
        axes(handles.picOutput2);
        Z = im2double(WatershedSegment(handles.image));
        Z = Z * 0.2;
        handles.image = Z + handles.image;
        imshow(handles.image);
        guidata(hObject, handles);
        disp("WaterShed Finished!")
        toc

        
        
    case 'Watershed2'
        tic
        axes(handles.picOutput2);
        I2 = imcomplement(handles.image);
        I3 = imhmin(I2,0.3);    %0.3 is the height threshold for suppressing shallow minima
        F = im2double(watershed(I3));
        handles.image = F + handles.image;
        imshow(handles.image);
        guidata(hObject, handles);
        disp("WaterSHED!")
        toc
    
        
        
    case 'Mean Shift Clustering'
        tic
        MSbw = 0.2;               %pixel by pixel similarity factor
        [Ims, Nms] = Ms(handles.image,MSbw); 
        axes(handles.picOutput2);
        [imsx,imsy,~] = size(handles.image);
        
        segmentedMSregions = Nms;
        meanShiftArea(segmentedMSregions,2) = 0;
        meanShiftArea = im2double(meanShiftArea);              % init area 2d array
        
        C = unique(Ims(:,:,1));
        for setup = 1:segmentedMSregions
            meanShiftArea(setup,1) = C(setup);
        end
        
        for m=1:imsx
           for n=1:imsy
               for region = 1:segmentedMSregions
                    if(meanShiftArea(region,1) == Ims(m,n,1))
                        meanShiftArea(region,2) = meanShiftArea(region,2) + 1.0;
                    end
                    
               end
            end
        end
        imageNumPixels = imsx * imsy;
        
        for calcArea = 1:segmentedMSregions
            meanShiftArea(calcArea,2) = ((meanShiftArea(calcArea,2) / imageNumPixels)*100);     %calculate area
        end
        
        q = uitable(handles.uitable2);
        set(q,'Data',meanShiftArea);                  % Used to change the area uitable properties.
        set(q,'ColumnName',{'region';'area'})
        set(q,'Visible','on');
        
        handles.image = Ims;
        imshow(Ims);
        title(['MeanShiftClusters: ',num2str(Nms)]);
        guidata(hObject, handles);
        disp("MS Done!")
        toc
end    
end







% --- Executes on button press in Submit_Button.
function Submit_Button_Callback(hObject, eventdata, handles)
% hObject    handle to Submit_Button (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
outputFilename = strcat(handles.SelectedAlgorithm, handles.SelectedImage);
imwrite(handles.image,outputFilename);
end





function Z=WatershedSegment(rgb)
I = rgb2gray(rgb);
imshow(I)
title("gray")
pause(2)

hy = fspecial('sobel');
hx = hy';
Iy = imfilter(double(I), hy, 'replicate');
Ix = imfilter(double(I), hx, 'replicate');
gradmag = sqrt(Ix.^2 + Iy.^2);
imshow(gradmag,[])
title("Sobel Edge Masks")
pause(2)

se = strel('disk', 20);
Ie = imerode(I, se);
Iobr = imreconstruct(Ie, I);
imshow(Iobr)
title("Opening By Reconstruction")
pause(2)

Iobrd = imdilate(Iobr, se);
Iobrcbr = imreconstruct(imcomplement(Iobrd), imcomplement(Iobr));
Iobrcbr = imcomplement(Iobrcbr);
imshow(Iobrcbr)
title("Opening-Closing By Reconstruction")
pause(2)

fgm = imregionalmax(Iobrcbr);
imshow(fgm)
title("Regional maxima of Opening-Closing By Reconstruction")
pause(2)

I2 = I;
I2(fgm) = 255;
imshow(I2)
title("Regional Maxima superimposed on original image")
pause(2)

se2 = strel(ones(5,5));
fgm2 = imclose(fgm, se2);
fgm3 = imerode(fgm2, se2);
fgm4 = bwareaopen(fgm3, 20);
I3 = I;
I3(fgm4) = 255;
imshow(I3)
title("Modified regional maxima superimposed on original image")
pause(2)

bw = imbinarize(Iobrcbr);
imshow(bw)
title("Threshold")
pause(2)

D = bwdist(bw);
DL = watershed(D);
bgm = DL == 0;
imshow(bgm)
title("Watershed Ridge Lines")
pause(2)

gradmag2 = imimposemin(gradmag, bgm | fgm4);
L = watershed(gradmag2);
I4 = I;
I4(imdilate(L == 0, ones(3, 3)) | bgm | fgm4) = 255;
imshow(I4)
title("Markers and object boundaries superimposed on original image")
pause(2)

Lrgb = label2rgb(L, 'jet', 'w', 'shuffle');
imshow(Lrgb)
title("Colored watershed label matrix")
Z = Lrgb;
end




function [J,colorMean]=regiongrowing(I,x,y,reg_maxdist,RegionVal)
% This function performs "region growing" in an image from a specified
% seedpoint (x,y)
% J = regiongrowing(I,x,y,t) 
% I : input image 
% J : logical output image of region
% x,y : the position of the seedpoint (if not given uses function getpts)
% t : maximum intensity distance (defaults to 0.2)
% The region is iteratively grown by comparing all unallocated neighbouring pixels to the region. 
% The difference between a pixel's intensity value and the region's mean, 
% is used as a measure of similarity. The pixel with the smallest difference 
% measured this way is allocated to the respective region. 
% This process stops when the intensity difference between region mean and
% new pixel become larger than a certain treshold (t)
% Example:
% I = im2double(imread('medtest.png'));
% x=198; y=359;
% J = regiongrowing(I,x,y,0.2); 
% figure, imshow(I+J);
% Author: D. Kroon, University of Twente

if(exist('reg_maxdist','var')==0), reg_maxdist=0.2; end
if(exist('y','var')==0), figure, imshow(I,[]); [y,x]=getpts; y=round(y(1)); x=round(x(1)); end

J = zeros(size(I)); % Output 
Isizes = size(I); % Dimensions of input image

redAverage = 0.0;
greenAverage = 0.0;
blueAverage = 0.0;

reg_mean = I(x,y); % The mean of the segmented region
reg_size = 1; % Number of pixels in region

% Free memory to store neighbours of the (segmented) region
neg_free = 10000; neg_pos=0;
neg_list = zeros(neg_free,3); 

pixdist=0; % Distance of the region newest pixel to the region mean

% Neighbor locations (footprint)
neigb=[-1 0; 1 0; 0 -1;0 1];

% Start regiogrowing until distance between region and posible new pixels become
% higher than a certain treshold

while(pixdist<reg_maxdist&&reg_size<numel(I))

    % Add new neighbors pixels
    for j=1:4
        % Calculate the neighbour coordinate
        xn = x +neigb(j,1); yn = y +neigb(j,2);
        
        % Check if neighbour is inside or outside the image
        ins=(xn>=1)&&(yn>=1)&&(xn<=Isizes(1))&&(yn<=Isizes(2));
        
        % Add neighbor if inside and not already part of the segmented area
        if(ins&&(J(xn,yn)==0)) 
                neg_pos = neg_pos+1;
                neg_list(neg_pos,:) = [xn yn I(xn,yn)]; 
                J(xn,yn) = RegionVal;
        end
    end

    % Add a new block of free memory
    if(neg_pos+10>neg_free), neg_free=neg_free+10000; neg_list((neg_pos+1):neg_free,:)=0; end
    
    % Add pixel with intensity nearest to the mean of the region, to the region
    dist = abs(neg_list(1:neg_pos,3)-reg_mean);
    [pixdist, index] = min(dist);
    %display("pixdist: " + pixdist)
    %display("index: " + index)
    J(x,y)=RegionVal;
    greenAverage = greenAverage + I(x,y,2);
    blueAverage = blueAverage + I(x,y,3);
    redAverage = redAverage + I(x,y,1);

    reg_size=reg_size+1;
    
    % Calculate the new mean of the region
    reg_mean= (reg_mean*reg_size + neg_list(index,3))/(reg_size+1);
    % Save the x and y coordinates of the pixel (for the neighbour add proccess)
    x = neg_list(index,1); y = neg_list(index,2);
    
    % Remove the pixel from the neighbour (check) list
    neg_list(index,:)=neg_list(neg_pos,:); neg_pos=neg_pos-1;
end
% Return the segmented area as logical matrix
greenAverage = greenAverage/reg_size;
blueAverage = blueAverage/reg_size;
redAverage = redAverage/reg_size;
colorMean = [redAverage,greenAverage,blueAverage];
end




function [clustCent,data2cluster,cluster2dataCell] = MeanShiftCluster(dataPts,bandWidth,plotFlag)
%perform MeanShift Clustering of data using a flat kernel
% ---INPUT---
% dataPts           - input data, (numDim x numPts)
% bandWidth         - is bandwidth parameter (scalar)
% plotFlag          - display output if 2 or 3 D    (logical)
% ---OUTPUT---
% clustCent         - is locations of cluster centers (numDim x numClust)
% data2cluster      - for every data point which cluster it belongs to (numPts)
% cluster2dataCell  - for every cluster which points are in it (numClust)
% Bryan Feldman 02/24/06
% MeanShift first appears in
% K. Funkunaga and L.D. Hosteler, "The Estimation of the Gradient of a
% Density Function, with Applications in Pattern Recognition"
%*** Check input ****

if nargin < 2
    error('no bandwidth specified')
end

if nargin < 3
    plotFlag = true;
    plotFlag = false;
end

%**** Initialize stuff ***
[numDim,numPts] = size(dataPts);
numClust        = 0;
bandSq          = bandWidth^2;
initPtInds      = 1:numPts;
maxPos          = max(dataPts,[],2);           %biggest size in each dimension
minPos          = min(dataPts,[],2);           %smallest size in each dimension
boundBox        = maxPos-minPos;               %bounding box size
sizeSpace       = norm(boundBox);              %indicator of size of data space
stopThresh      = 1e-3*bandWidth;              %when mean has converged
clustCent       = [];                          %center of clust
beenVisitedFlag = zeros(1,numPts,'uint8');     %track if a points been seen already
numInitPts      = numPts;                      %number of points to posibaly use as initilization points
clusterVotes    = zeros(1,numPts,'uint16');    %used to resolve conflicts on cluster membership


while numInitPts

    tempInd         = ceil( (numInitPts-1e-6)*rand);     %pick a random seed point
    stInd           = initPtInds(tempInd);               %use this point as start of mean
    myMean          = dataPts(:,stInd);                  % intilize mean to this points location
    myMembers       = [];                                % points that will get added to this cluster                          
    thisClusterVotes    = zeros(1,numPts,'uint16');      %used to resolve conflicts on cluster membership

    while 1     %loop untill convergence
        
        sqDistToAll = sum(bsxfun(@minus,myMean,dataPts).^2);    %dist squared from mean to all points still active
        inInds      = find(sqDistToAll < bandSq);               %points within bandWidth
        thisClusterVotes(inInds) = thisClusterVotes(inInds)+1;  
        %add a vote for all the in points belonging to this cluster
        
        
        myOldMean   = myMean;                                   %save the old mean
        myMean      = mean(dataPts(:,inInds),2);                %compute the new mean
        myMembers   = [myMembers inInds];                       %add any point within bandWidth to the cluster
        beenVisitedFlag(inInds) = 1;                         %mark that these points have been visited
        
        %*** plot stuff ****
        if plotFlag
            figure(12345),clf,hold on
            if numDim == 2
                plot(dataPts(1,:),dataPts(2,:),'.')
                plot(dataPts(1,myMembers),dataPts(2,myMembers),'ys')
                plot(myMean(1),myMean(2),'go')
                plot(myOldMean(1),myOldMean(2),'rd')
                pause
            end
        end

        %**** if mean doesn't move much stop this cluster ***
        if norm(myMean-myOldMean) < stopThresh
            
            %check for merge posibilities
            mergeWith = 0;
            for cN = 1:numClust
                distToOther = norm(myMean-clustCent(:,cN));     
                %distance from posible new clust max to old clust max
                if distToOther < bandWidth/2                    
                    %if its within bandwidth/2 merge new and old
                    mergeWith = cN;
                    break;
                end
            end
            
            
            if mergeWith > 0    % something to merge
                clustCent(:,mergeWith)       = 0.5*(myMean+clustCent(:,mergeWith));             
                %record the max as the mean of the two merged (I know biased twoards new ones)
                %clustMembsCell{mergeWith}    = unique([clustMembsCell{mergeWith} myMembers]);   
                %record which points inside 
                clusterVotes(mergeWith,:)    = clusterVotes(mergeWith,:) + thisClusterVotes;    
                %add these votes to the merged cluster
            else    %its a new cluster
                numClust                    = numClust+1;                   %increment clusters
                clustCent(:,numClust)       = myMean;                       %record the mean  
                %clustMembsCell{numClust}    = myMembers;                    %store my members
                clusterVotes(numClust,:)    = thisClusterVotes;
            end

            break;
        end

    end
    
    initPtInds      = find(beenVisitedFlag == 0);           
    %we can initialize with any of the points not yet visited
    numInitPts      = length(initPtInds);                   
    %number of active points in set

end

[val,data2cluster] = max(clusterVotes,[],1);                
%a point belongs to the cluster with the most votes

%*** If they want the cluster2data cell find it for them
if nargout > 2
    cluster2dataCell = cell(numClust,1);
    for cN = 1:numClust
        myMembers = find(data2cluster == cN);
        cluster2dataCell{cN} = myMembers;
    end
end
end




function [Ims Kms] = Ms2(I,bandwidth)

% color + spatial (option: bandwidth)
I = im2double(I);
[x,y] = meshgrid(1:size(I,2),1:size(I,1)); L = [y(:)/max(y(:)),x(:)/max(x(:))]; % Spatial Features
C = reshape(I,size(I,1)*size(I,2),3); X = [C,L];                                % Color & Spatial Features
% MeanShift Segmentation
[clustCent,point2cluster,clustMembsCell] = MeanShiftCluster(X',bandwidth);      % MeanShiftCluster
for i = 1:length(clustMembsCell)                                                % Replace Image Colors With Cluster Centers
X(clustMembsCell{i},:) = repmat(clustCent(:,i)',size(clustMembsCell{i},2),1); 
end
Ims = reshape(X(:,1:3),size(I,1),size(I,2),3);                                  % Segmented Image
Kms = length(clustMembsCell);

end




function [Ims Kms] = Ms(I,bandwidth)

% Mean Shift Segmentation (option: bandwidth)
I = im2double(I);
X = reshape(I,size(I,1)*size(I,2),3);                                         % Color Features
% MeanShift
[clustCent,point2cluster,clustMembsCell] = MeanShiftCluster(X',bandwidth);    % MeanShiftCluster
for i = 1:length(clustMembsCell)                                              % Replace Image Colors With Cluster Centers
X(clustMembsCell{i},:) = repmat(clustCent(:,i)',size(clustMembsCell{i},2),1); 
end
Ims = reshape(X,size(I,1),size(I,2),3);                                         % Segmented Image
Kms = length(clustMembsCell);

end

function mtestsp(pflag);
% mtestsp
%   This Matlab script can be used to test your spline 
%   interpolation with different boundary conditions
%   Assumes data.txt contains the data points 
%
% Start matlab, then type the command: mtestsp    or mtestsp(1)
% Note:  Xwindows is required to display the plots
%
% Usage: mtestsp(pflag)
%          pflag = integer, 1 to show plots and save to figures, requires Xwindows
%
% Preconditions:
%   * first line of data file contains derivatives (will be ignored
%     for natural and not-a-knot cases)
%
% Side effects:
%       Plots a figure of the spline interpolant
%       save figures to files 

% Written by: Juan C. Cockburn, 
% Revised: Nov 17, 2014 (jcck@ieee.org)
%          Nov 11, 2015 R. Repka

% Read data points
if nargin==0
    help mtestsp
    pflag=0;
end

% Load data
  datafile='data.txt';
  [pathstr,Data,ext]= fileparts(datafile);
  fname=[Data ext];
  eval(['load -ascii ' fname]);
  eval(['Data=' Data]);
% Extract first line (with derivatives)
  % Clampled boundary conditions;
      yp0 = Data(1,1); % At first point
	  ypn = Data(1,2); % At last point
  % Data Points
       x = Data(2:end,1)'; % Note the transpose operator
       y = Data(2:end,2)'; % Note the transpose operator

% Find the clamped cubic spline interpolant
       ccs = csape(x,y,'complete',[yp0 ypn]);

% Find the natural cubic spline interpolant
       ncs = csape(x,y,'second',[0 0]);

% Find the not-a-knot cubic spline interpolant
       kcs = csape(x,y,'not-a-knot');

% Show results

% Show results: clamped case
     format short
     fprintf('Not-a-knot spline parameters d,c,b,a\n')
     disp(kcs.coefs)

     fprintf('Natural spline parameters d,c,b,a\n')
     disp(ncs.coefs)

     fprintf('Clamped spline parameters d,c,b,a\n')
     disp(ccs.coefs)

% Draw Plots
  if pflag
     disp('Plotting the results')
     figure(1)
     fnplt(kcs); axis equal
     hold on
	 plot(x,ppval(kcs,x),'or'); % plot points
     title('Not-a-Knot Cubic Spline Interpolant')
     xlabel('x');ylabel('y')

     figure(2)
     fnplt(ncs); axis equal
     hold on
	 plot(x,ppval(ncs,x),'or'); % plot points
     title('Natural Cubic Spline Interpolant')
     xlabel('x');ylabel('y')

     figure(3)
     fnplt(ccs); axis equal
     hold on
	 plot(x,ppval(ccs,x),'or'); % plot points
     title('Clamped Cubic Spline Interpolant')
     xlabel('x');ylabel('y')
  
  % Save figures to files
     print -f1 -dpng notaknot_splines.png
     print -f2 -dpng natural_splines.png
     print -f3 -dpng clampled_splines.png
  end % pflag

return


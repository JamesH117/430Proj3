# 430Proj3
CS430 Project 3 James Hauser Jh2377 Project 3 - Illumination

Run the make file.  Once created the parameters for the .exe is: "pixel_width" "Pixel_height" "Json_file.json" "output_name.ppm"

Problems resolved thanks to Dr. Palmer
# Problems with project:
	Shading seems to bugged.  Problem is most likely that my intersection test for shadows is colliding with self object somehow, even though I skip closest
		object, which is itself.
	Planes will sometimes not color if the normal is positive.  The plane is still rendered in 3d space but the color is not added.  I believe this is also because
		of the above issue where intersection are colliding with self object for shadowing.

	Need to go to Palmer Office Hours to gain assistance with these problems.

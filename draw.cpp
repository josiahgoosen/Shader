#include "draw.h"


/////////////////
// Function   : draw()
// Parameters : int width		number of columns
//              int height		number of rows
//              HDC &img		windows image buffer
//				Scene scene		information about the scene (see scene.h)
//
/////////////////
void draw(
	int width,
	int height,
	HDC &img,
	Scene scene)
{
	int size = scene.model.face.size();

	for (int i = 0; i < size; i++) {
		vec4f A = scene.model.vertex[scene.model.face[i][0].vertex]; // read vertices into temp variables A, B, C
		vec4f B = scene.model.vertex[scene.model.face[i][1].vertex];
		vec4f C = scene.model.vertex[scene.model.face[i][2].vertex];

		sortVertices(A, B, C);

		float DeltaX_CA = (A.x - C.x) / (A.y - C.y);
		float DeltaX_BA = (A.x - B.x) / (A.y - B.y);
		float Cx = C.x;
		float Bx = B.x;



		for (int y = (int)C.y; y <= (int)A.y; y++) {
			for (int x = (int)Cx; x <= (int)Bx; x++) {
				SetPixel(img, x, y, RGB(255, 0, 0));
			}
			Cx += DeltaX_CA;
			Bx += DeltaX_BA;
		}

		SetPixel(img, A.x, A.y, RGB(255, 0, 0));
		SetPixel(img, B.x, B.y, RGB(0, 255, 0));
		SetPixel(img, C.x, C.y, RGB(0, 0, 255));
	}

	// Draw 4 squares in the image
	//for (int y = 0; y < height; y++)
	//{
	//	for (int x = 0; x < width; x++)
	//	{
	//		if (x < width / 2)
	//			if (y < height / 2)
	//				// Top left is Red
	//				SetPixelV(img, x, y, RGB(255, 0, 0));
	//			else
	//				// Bottom left is Green
	//				SetPixelV(img, x, y, RGB(0, 255, 0));
	//		else
	//			if (y < height / 2)
	//				// Top Right is Blue
	//				SetPixelV(img, x, y, RGB(0, 0, 255));
	//			else
	//				// Bottom right is White
	//				SetPixelV(img, x, y, RGB(255, 255, 255));
	//	}
	//}
}

void sortVertices(vec4f &A, vec4f &B, vec4f &C) {
	vec4f first = A;
	vec4f second = B;
	vec4f third = C;
	
	//check if the first vec4f is the highest, if y's are equal, choose the one further to the left as A
	if (first.y < second.y && first.y < third.y) {
		A = first;
	}
	else if (first.y == second.y && first.y < third.y) {
		if (first.x < second.x) {
			A = first;
		}
		else {
			A = second;
		}
	}
	else if (first.y < second.y && first.y == third.y) {
		if (first.x < third.x) {
			A = first;
		}
		else {
			A = third;
		}
	}

	//check if the second vec4f is the highest, if y's are equal, choose the one further to the left as A
	if (second.y < first.y && second.y < third.y) {
		A = second;
	}
	else if (second.y == first.y && second.y < third.y) {
		if (second.x < first.x) {
			A = second;
		}
		else {
			A = first;
		}
	}
	else if (second.y < first.y && second.y == third.y) {
		if (second.x < third.x) {
			A = second;
		}
		else {
			A = third;
		}
	}

	//check if the third vec4f is the highest, if y's are equal, choose the one further to the left as A
	if (third.y < second.y && third.y < first.y) {
		A = third;
	}
	else if (third.y == second.y && third.y < first.y) {
		if (third.x < second.x) {
			A = third;
		}
		else {
			A = second;
		}
	}
	else if (third.y < second.y && third.y == first.y) {
		if (third.x < first.x) {
			A = third;
		}
		else {
			A = first;
		}
	}

	//if A is first, find the next one clockwise to the right and choose it as B, then assign C
	if (A == first) {
		if (second.y < third.y) {
			B = second;
			C = third;
		}
		else if (second.y == third.y) {
			if (second.x > third.x) {
				B = second;
				C = third;
			}
			else {
				B = third;
				C = second;
			}
		}
		else {
			B = third;
			C = second;
		}
	}

	//if A is second, find the next one clockwise to the right and choose it as B, then assign C
	if (A == second) {
		if (first.y < third.y) {
			B = first;
			C = third;
		}
		else if (first.y == third.y) {
			if (first.x > third.x) {
				B = first;
				C = third;
			}
			else {
				B = third;
				C = first;
			}
		}
		else {
			B = third;
			C = first;
		}
	}

	//if A is third, find the next one clockwise to the right and choose it as B, then assign C
	if (A == third) {
		if (second.y < first.y) {
			B = second;
			C = first;
		}
		else if (second.y == first.y) {
			if (second.x > first.x) {
				B = second;
				C = first;
			}
			else {
				B = first;
				C = second;
			}
		}
		else {
			B = first;
			C = second;
		}
	}
}

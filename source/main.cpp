/*
Title: Projection and Rejection
File Name: main.cpp
Copyright © 2016
Author: Andrew Litfin
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// The bread and butter of games programming is vector mathematics and linear algebra.
// The vast majority of the mathematics used in games falls under this category,
//  though it is not the only math used (e.g. discrete math, calculus).
// This tutorial series will take you through the basics of vector math.
// Future tutorials in this series will detail other aspects of linear algebra, particularly matrices.
// The exposition follows that of "Foundations of Game Engine Development" (Volume 1),
//  by Eric Lengyel.
// This file provides exposition, definitions, and explanations, and all other files implement vector classes
//  as you would see them in most game engines. The implementations are modeled after those of Eric Lengyel
//  in FGED, Volume 1 and the Tombstone Engine, though they are my own.
// Only Vector2D.h is heavily annotated, the others are mostly identical.

// This tutorial explains the projection and rejection operations.

#include "../header/helpers.h"
#include "../header/Vector2D.h"
#include "../header/Vector3D.h"
#include "../header/Vector4D.h"

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
	// Required for the random functions in helpers to work.
	srand(static_cast<unsigned>(time(0)));

	// Projection
	// ----------
	{
		// Projecting one vector onto another has many applications in games and simulation.

		// Given two vectors a and b, the projection of a onto b is most often notated as proj_b(a)

		// Geometrically, it puts one vector "onto" another, with the length proportional to the length of the first.
		// For example,
		/*

          b
          ^
          |
          |    a
proj_b(a) ^----^
          |   /
          |  /
          | /
          |/
          /

		*/

		// This means that proj_b(a) is actually a scalar multiple of b, where the scalar is dependent on a.
		// I.E., proj_b(a) = comp_b(a)*b^, where comp_b(a) is the component of a in the direction of b, and b^ = b/|b|

		// Because the first vector is "dropped" straight down onto the second, there is a right angle where they meet.
		// As such, we can use triginometry to find comp_b(a). Recalling the cosine function,
		//  if theta is the angle between a and b, then cos(theta) = comp_b(a)/|a|,
		//  hence comp_b(a) = |a|cos(theta).

		// Look somewhat familiar?

		// Because multiplying by 1 doesn't change the result, we can multiply by |b|/|b|.

		// Now comp_b(a) = |a||b|cos(theta)/|b| = Dot(a, b)/|b|
		// Then proj_b(a) = Dot(a, b)/|b| * b^ = Dot(a, b)/|b| * b/|b| = Dot(a, b)/|b|^2 * b = Dot(a, b)/Dot(b, b) * b.

		// The last form is the most computationally efficient, unless it is already known that b is a unit vector, in which case
		// proj_b^(a) = Dot(a, b^) * b^
		
		// The following code shows how the projection operation is NOT commutative:
		Vector3D a = Vector3D(randFloat(-10, 10), randFloat(-10, 10), randFloat(-10, 10));
		Vector3D b = Vector3D(randFloat(-10, 10), randFloat(-10, 10), randFloat(-10, 10));
		std::cout << "a = " << a << ", b = " << b
			<< "\nproj_b(a) = " << Project(a, b)
			<< "\nproj_a(b) = " << Project(b, a) << "\n";


		// To illustrate the projection operator's usefulness, see [this highly academic paper by Zach Weinersmith](http://smbc-comics.com/index.php?id=3870).


		// Here's a use case of projection in simulation:
		// Say you have a cart on a track that can only move forward or backward, and the player character can push on the cart at any angle.
		// Say the player character decides to push on the cart at a right angle to the track.
		// If all your code says is "if the player pushes on the cart, move it forward," then it looks rather unrealistic.
		// Instead you would want the cart to be unaffected.
		// If the player instead pushes at a slight angle, you would want the cart to have a small acceleration,
		//  and if the player pushes the cart in line with the track, you would want the cart to have a larger acceleration.
		// How can you have one mathematical function that does all these things?
		// Enter: vector projection.

		// When the player pushes on the cart, they exert some force on the cart in the direction that they are pushing
		//  with magnitude relative to their strength.
		// The cart can only move forward or backward, so we need the component of force in the direction of possible motion for the cart,
		//  and that will give us the net force on the cart, and from there, the acceleration.
		// So, if the force exerted is Fpush and the direction of motion d, then the net force acting on the cart is F = proj_d(Fpush).
		Vector3D Fpush = Vector3D(randFloat(-5, 5), randFloat(-5, 5), randFloat(-5, 5)); // The bounds of -5, 5 in each direction are arbitrary.
		Vector3D d = Vector3D(1, 0, 0);

		std::cout << "Fpush: " << Fpush << "\nF = proj_d(Fpush) = " << Project(Fpush, d) << "\n";
	}

	// Rejection
	// ---------
	{
		// Rejection is a less commonly used operator, but is still useful to know.

		// Where Projection puts one vector onto another, Rejection takes one vector away from another.
		// The geometric interpretation is as follows:

		/*
              a
              ^
             /| Reject(a, b)
            / |
           /  |
          /   |
         /---------> b

		*/

		// In particular, we have that Reject(a, b) is always perpendicular to b.
		// Reject(a, b) is easily calculated as Reject(a, b) = a - Project(a, b).
		// We call Reject(a, b) the vector rejection of a from b.
		// It is sometimes notated as the vector name with a subscript perpendicular symbol (also called an up tack).

		// Interestingly, this gives the relation a = Project(a, b) + Reject(a, b).

		// Thus we have a way to decompose any vector a into two parts, dependent on another vector b:
		// The part of a parallel to b, and the part of a perpendicular to b.

		Vector3D a = { randFloat(0, 1), randFloat(0, 1), randFloat(0, 1) };
		Vector3D b = { randFloat(0, 1), randFloat(0, 1), randFloat(0, 1) };

		Vector3D aParallel = Project(a, b);
		Vector3D aPerp = Reject(a, b);

		if (aParallel + aPerp == a)
		{
			std::cout << "a = " << a << ", b = " << b << "\naParallel = " << aParallel << ", aPerp = " << aPerp
				<< "\nHence " << aParallel << " + " << aPerp << " = " << a << "\n";
		}
	}

	std::cout << "Press Enter to continue . . . ";
	std::cin.get();
	return 0;
}

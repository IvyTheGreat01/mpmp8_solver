// Ivan Bystrov
// Code to solve Matt Parker's Math Puzzle 8

#include <stdio.h>

// A node representing a face of the stack
// Its a struct because it used to have more info regarding folds which I later realized was unnecessary
typedef struct Face {
	int id;
} Face;

// An array of faces
Face all_faces[6];

// ilc stands for is_legal_connection
// Checks if the proposed connection is possible in real world
// start_conn_1, end_conn1 is the first set of faces being connected
// start_conn_2, end_conn2 is the second set of faces being connected
// The assumption is that both connections happen along the same side of the completed stack 
int ilc(int start_conn_1, int end_conn_1, int start_conn_2, int end_conn_2) {
	// Check if one of the connections of the first set is less than the other
	if (start_conn_1 < end_conn_1) {
		// Check if one of the connections of the second set is between the connections of the first set
		if (start_conn_2 > start_conn_1 && start_conn_2 < end_conn_1) {
			// Check if the other connection of the second set is outside the connections of the first set
			if (end_conn_2 < start_conn_1 || end_conn_2 > end_conn_1) {
				return 0;
			}
		}

		// Check if the other connection of the second set is between the connecetions of the first set
		else if (end_conn_2 > start_conn_1 && end_conn_2 < end_conn_1) {
			// Check if the other connection of the second set is outside the connections of the first set
			if (start_conn_2 < start_conn_1 || start_conn_2 > end_conn_1) {
				return 0;
			}
		}
	}
	
	// Check if the other connection of the first set is less than the other
	else if (end_conn_1 < start_conn_1) {
		// Check if one of the connections of the second set is between the connections of the first set
		if (start_conn_2 > end_conn_1 && start_conn_2 < start_conn_1) {
			// Check if the other connection of the second set is outside the connections of the first set
			if (end_conn_2 < end_conn_1 || end_conn_2 > start_conn_1) {
				return 0;
			}
		}
		
		// Check if the other connection of the second set is between the connections of the first set
		else if (end_conn_2 > end_conn_1 && end_conn_2 < start_conn_1) {
			// Check if the other connection of the second set is outside the connections of the first set
			if (start_conn_2 < end_conn_1 || start_conn_2 > start_conn_1) {
				return 0;
			}
		}
	}

	return 1;
}


int main() {
	int total_correct = 0;

	// Create the 8 faces
	for (int i = 0; i < 8; i++) {
		Face face;
		face.id = 0;
		all_faces[i] = face;
	}

	// Choose 1 (A) Face
	all_faces[0].id = 1;
	int one_face = 0;
	
	// 1 (A) connection with the 2 face (choose 2 face)
	for (int two_face = 0; two_face < 8; two_face++) {
		if (all_faces[two_face].id == 0) {
			all_faces[two_face].id = 2;

			// 1 (A) connection with the 3 face (choose 3 face)
			for (int three_face = 0; three_face < 8; three_face++) {
				if (all_faces[three_face].id == 0) {
					all_faces[three_face].id = 3;

					// 2 connection with the 4 face and 3 connection with the four face (choose 4 face)
					for (int four_face = 0; four_face < 8; four_face ++) {
						if (all_faces[four_face].id == 0 && ilc(one_face, three_face, two_face, four_face) && ilc(one_face, two_face, three_face, four_face)) {
							all_faces[four_face].id = 4;

							// 3 connection with the 5 face (choose 5 face)
							for (int five_face = 0; five_face < 8; five_face++) {
								if (all_faces[five_face].id == 0) {
									all_faces[five_face].id = 5;

									// 4 connection to the 6 face and 5 connection with 6 face (choose 6 face)
									for (int six_face = 0; six_face < 8; six_face ++) {
										if (all_faces[six_face].id == 0 && ilc(four_face, six_face, three_face, five_face) && ilc(five_face, six_face, one_face, two_face) && ilc(five_face, six_face, three_face, four_face)) {
											all_faces[six_face].id = 6;

											// 5 connection with 7 face (choose 7 face)
											for (int seven_face = 0; seven_face < 8; seven_face ++) {
												if (all_faces[seven_face].id == 0 && ilc(seven_face, five_face, one_face, three_face) && ilc(seven_face, five_face, two_face, four_face)) {
													all_faces[seven_face].id = 7;

													// 6 connection with 8 face and 7 connection with 8 face
													for (int eight_face = 0; eight_face < 8; eight_face ++) {
														if (all_faces[eight_face].id == 0 && ilc(eight_face, six_face, one_face, three_face) && ilc(eight_face, six_face, two_face, four_face) && ilc(eight_face, six_face, five_face, seven_face) && ilc(eight_face, seven_face, one_face, two_face) && ilc(eight_face, seven_face, three_face, four_face) && ilc(eight_face, seven_face, five_face, six_face)) {
															all_faces[eight_face].id = 8;
															
															// Increment total number of correct solutions
															total_correct ++;
															fprintf(stderr, " %d\n", total_correct);
																
															// Draw top row of the starting grid
															for (int i = 1; i < 9; i += 2) {
																for (int j = 0; j < 8; j++) {
																	if (all_faces[j].id == i) { 
																		fprintf(stderr, " %c", 65 + j);
																	}
																}
															}
															
															fprintf(stderr, "\n");

															// Draw the bottom row of the starting grid
															for (int i = 2; i < 10; i += 2) {
																for (int j = 0; j < 8; j++) {
																	if (all_faces[j].id == i) {
																		fprintf(stderr, " %c", 65 + j);	
																	}			
																}
															}

															fprintf(stderr, "\n\n");

															// Clear the eight face
															all_faces[eight_face].id = 0;
														}
													}

													// Clear the seven face
													all_faces[seven_face].id = 0;
												}	
											}

											// Clear the six face
											all_faces[six_face].id = 0;
										}
									}

									// Clear the five face
									all_faces[five_face].id = 0;
								}
							}

							// Clear the four face
							all_faces[four_face].id = 0;
						}
					}

					// Clear three face
					all_faces[three_face].id = 0;
				}
			}

			// Clear two face
			all_faces[two_face].id = 0;
		}
	}

	printf("Total Possible Starting Grids: %d\n", total_correct);
	return 0;	
}

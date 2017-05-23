#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "plain.h"
#include "vector.h"

/*Point *get_third_point(Plain *plain, Point *p, Point *q)
{
    if (plain->b == p && plain->a == q)
        return plain->c;
    if (plain->a == p && plain->c == q)
        return plain->b;
    if (plain->c == p && plain->b == q)
        return plain->a;

}*/

Plain *get_neighbor(Plain *plain, Point *p, Point *q)
{
    if (plain->b == p && plain->a == q)
        return plain->ba;
    if (plain->a == p && plain->c == q)
        return plain->ac;
    if (plain->c == p && plain->b == q)
        return plain->cb;
}

void get_neighbors_points(Plain *plain, Plain *neighbor, Point **a, Point **b, Point **c)
{

    Node *plain_points = append_list(get_points(plain), get_points(plain));
    Node *neighbor_points = append_list(get_points(neighbor), get_points(neighbor));
	
	/* for each two adjacent points of plain 
	 * checking whether they are the same as two adjacent points of neighbor
	 * 
	 * point and point.next gives two adjacent points
	 * if next is null then just first point is observed
	 * 
	 * loop by plain_points, inside loop by neighbor points 
	 */
    for (Node *p = plain_points; p->next != NULL; p = p->next) {
		for(Node *n = neighbor_points; n->next->next != NULL; n = n->next) {
            if (p->elem == n->next->elem && p->next->elem == n->elem){
                *a = n->elem;
                *b = n->next->elem;
                *c = n->next->next->elem;
                break;
            }
        }
    }
}

void add_neighbors(Plain *plain, Node *list)
{
    for (Node *temp = list; temp != NULL; temp = temp->next) {
        Plain * temp_plain = (Plain *)temp->elem;

        if (temp_plain == plain) continue;
        
        Node *neighbor_points = append_list(get_points(temp_plain), get_points(temp_plain));
       
        for(Node *n = neighbor_points; n->next != NULL; n = n->next) {

			Point *q = n->elem, *p = n->next->elem;

            if (q == plain->b && p == plain->a)
                plain->ba = temp_plain;
            if (q == plain->a && p == plain->c)
                plain->ac = temp_plain;
            if (q == plain->c && p == plain->b)
                plain->cb = temp_plain;
			
			/*if (p == plain->b && q == plain->a)
                plain->ba = temp_plain;
            if (p == plain->a && q == plain->c)
                plain->ac = temp_plain;
            if (p == plain->c && q == plain->b)
                plain->cb = temp_plain;*/
        }
    }
}

void arrange_points(Node *plains, Node *points)
{
    for (Node *temp = points; temp != NULL; temp = temp->next) {
        Point *point = (Point *)temp->elem;

	for (Node *temp = plains; temp != NULL; temp = temp->next) {
            Plain *plain = (Plain *)temp->elem;

			if (distance(*plain, *point) > 0.0001) { // <- since they are doubles
                plain->points = add_node(plain->points,point);
				break;
            }
        }
    }
}

Node* initial_convex_hull(Node *points)
{
    Point *point = (Point *)points->elem;
    double minx = point->x, miny = point->y, minz = point->z;
    double maxx = point->x, maxy = point->y, maxz = point->z;
    Point *pminx = point, *pminy = point, *pminz = point;
    Point *pmaxx = point, *pmaxy = point, *pmaxz = point;
	
    for (Node *temp = points; temp != NULL; temp = temp->next) {
        point = (Point *)temp->elem;
        if (point->x > maxx) {	
            maxx = point->x;
            pmaxx = point;
        }
        if (point->x < minx) {
            minx = point->x;
            pminx = point;
		}
        if (point->y > maxy) {
            maxy = point->y;
            pmaxy = point;
        }
        if (point->y < miny) {
            miny = point->y;
            pminy = point;
        }
        if (point->z > maxz) {
            maxz = point->z;
            pmaxz = point;
        }
        if (point->z < minz) {
            minz = point->z;
            pminz = point;
        }
    }
   
   	Point *xyzpoints [] = {pminx,pmaxx,pminz,pmaxz,pminy,pmaxy};
	
	double max_dist = 0;
	Point *a,*b, *c;
	
	/* Two farthest points from xyzpoints. */
	int i,j;
	for (i = 0; i < 6; i++) {
		for(j = 0; j < 6; j++) {
			if(i==j) continue;
			
			double dist = vector_length(sub_vector(*xyzpoints[i], *xyzpoints[j]));
			
			if(dist > max_dist) {
				max_dist = dist;
				a = xyzpoints[i];
				b = xyzpoints[j];
			}
		}
	}
	
	/* Finding point that is farthest from ab line. */
	max_dist = 0;
	for (Node *temp = points; temp != NULL; temp = temp->next) {
		Point *point = temp->elem;
		
		double dist = point_to_line_distance(*point, *a, *b);
		
		if(abs(dist) > max_dist) {
			max_dist = abs(dist);
			
			c = point;
		}
	}
	
	Node * list = NULL;
	
	Plain *plain = make_plain(a,b,c);
	plain->points = points;
	
	Point *top = find_farthest_point(*plain);
	
	plain = make_plain(c,b,a);
	list = add_node(list,plain);
	
	Point *abc [] = {a,b,c};
    for (i = 0; i < 3; i++){
        Plain *plain = make_plain(top,abc[i],abc[(i+1)%3]);
        list = add_node(list,plain);
    }
   
    for (Node *temp = list; temp != NULL; temp = temp->next) {
        Plain * temp_plain = (Plain *)temp->elem;
        add_neighbors(temp_plain,list);
    }
    
    arrange_points(list,points);

    return list;
}

Node *convex_hull(Node *points)
{

    Node *plains = initial_convex_hull(points);

	for (Node *temp = plains; temp != NULL; temp = temp->next) {
        Plain *plain = (Plain *)temp->elem;
		
//      does points above this plain exists
// 		if not, it's not needed to be processed
		
		if (plain->points == NULL) continue;		
//      the farthest point from plain surely belongs to convex hull
		
		Point *point = find_farthest_point(*plain);

//      put points of a plain in set of unassigned points
		Node *plain_points = plain->points;
        plain->points = NULL; // <- so this plain has no points
       
//      now creates list of new plains and their neighbors
        Node *new_plains = NULL, *new_plains_neighbors = NULL;
        for (Node *curr = get_neighbors(plain); curr != NULL; curr = curr->next){
            Plain *neighbor = (Plain *)curr->elem;
			Point *na, *nb, *nc; // find points of a neighbor
			get_neighbors_points(plain, neighbor, &na, &nb, &nc);
			
            if (distance(*neighbor,*point) > 0){

				// put points in set of unarranged points
				plain_points = append_list(plain_points, neighbor->points);

				// create new plains na_point_nc and point_nb_nc
                new_plains = add_node(new_plains, make_plain(na, point, nc));
                new_plains = add_node(new_plains, make_plain(point, nb, nc));
                
                // add new neighbors neighbors from sides na_nc and nb_nc
				new_plains_neighbors = 				add_node(new_plains_neighbors,get_neighbor(neighbor,na,nc));
                new_plains_neighbors = add_node(new_plains_neighbors,get_neighbor(neighbor,nb,nc));
            } else {
                // create new plain a_b_point
				new_plains = add_node(new_plains, make_plain(na, point, nb));
               
                // add neighbor	on the side of a_b 
				new_plains_neighbors = add_node(new_plains_neighbors, neighbor);
            }
        }
               
        // linkage of neighbors
        for (Node *i = new_plains; i != NULL; i = i->next){
            add_neighbors(i->elem, new_plains);
            add_neighbors(i->elem, new_plains_neighbors);
        }
        
        for (Node *i = new_plains_neighbors; i != NULL; i = i->next){
			Plain *plain = (Plain *)i->elem;
			add_neighbors(i->elem,new_plains);
        }
        // arrange points from plain_points to new_plains
		arrange_points(new_plains, plain_points);
        // now add new_plains to the end of all plains in space
        plains = append_list(plains, new_plains);
    }
    return plains;
}

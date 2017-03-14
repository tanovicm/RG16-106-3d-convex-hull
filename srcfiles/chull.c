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

Plain *get_neighboor(Plain *plain, Point *p, Point *q)
{
    if (plain->b == p && plain->a == q)
        return plain->ba;
    if (plain->a == p && plain->c == q)
        return plain->ac;
    if (plain->c == p && plain->b == q)
        return plain->cb;
}



void get_neighboors_points(Plain *plain, Plain *neighboor, Point **a, Point **b, Point **c)
{
	printf("\nGET POINTS ...\n");
	print_point(get_points(neighboor));
	printf("\nGET POINTS leaving ...\n");
	
    Node *plain_points = append_list(get_points(plain), get_points(plain));
    Node *neighboor_points = append_list(get_points(neighboor), get_points(neighboor));
	
	
    /*sad treba za svake dve susedne tacke od plain da vidimo da li su one iste kao dve susedne tacke od nejbor*/
    /*dve susedne tack dobijamo sa point, point.next ako je point.next != null a ako je null onda prva
     znaci samo imamo petlju po plain_points i u njoj petlju po neighboor_points ajdeeeeeeeeeeee*/

    for (Node *p = plain_points; p->next != NULL; p = p->next) {
		for(Node *n = neighboor_points; n->next->next != NULL; n = n->next) {
            if (p->elem == n->next->elem && p->next->elem == n->elem){
                *a = n->elem;
                *b = n->next->elem;
                *c = n->next->next->elem;
                break;
            }
        }
    }
}



// dodaje sve susede trouglu plain iz liste list
void add_neighboors(Plain *plain, Node *list)
{
	printf("add_neighboors entering..\n");
    for (Node *temp = list; temp != NULL; temp = temp->next) {
        Plain * temp_plain = (Plain *)temp->elem;

        if (temp_plain == plain) continue;
        
        Node *neighboor_points = append_list(get_points(temp_plain), get_points(temp_plain));
       
        for(Node *n = neighboor_points; n->next != NULL; n = n->next){
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
        printf("add_neighboors leaving..\n");
}

void arrange_points(Node *plains, Node *points)
{
    for (Node *temp = points; temp != NULL; temp = temp->next) {
        Point *point = (Point *)temp->elem;
	print_point(point);
	printf("\n");
        for (Node *temp = plains; temp != NULL; temp = temp->next) {
            Plain *plain = (Plain *)temp->elem;
            
	    printf("%lf\n", distance(*plain, *point));
	    
            if (distance(*plain, *point) > 0.0001){
                plain->points = add_node(plain->points,point);
		break;
            }
        }
    }
}

Node * initial_convex_hull(Node *points)
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
	
	max_dist = 0;
	for (Node *temp = points; temp != NULL; temp = temp->next) {
		Point *point = temp->elem;
		
		double dist = point_to_line_distance(*point, *a, *b);
		
		if(abs(dist) > max_dist) {
			max_dist = abs(dist);
			
			c = point;
		}
	}
	
	print_point(a);print_point(b); print_point(c);printf("abc \n");
	
	Node * list = NULL;
	
	Plain *plain = make_plain(a,b,c);
	plain->points = points;
	
	print_plain(plain); printf("plains \n");
	
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
        add_neighboors(temp_plain,list);
    }
    
    arrange_points(list,points);

    return list;
}

Node *convex_hull(Node *points)
{
	
    // Inicijalni konveksni omotac
    Node *plains = initial_convex_hull(points);
    
	print_list(plains, print_plain);
	
    for (Node *temp = plains; temp != NULL; temp = temp->next) {
        Plain *plain = (Plain *)temp->elem;
		printf("\nofje1\n");
        // Da li postoje tacke iznad ove strane, ako nepostoje nemamo sta da radimo sa njom
        if (plain->points == NULL) continue;
		// najdalja tacka od strane sigurno pripada konveksnom omotacu
        Point *point = find_farthest_point(*plain);
        // stavi tacke u skup nerasporedjenih tackaka
        Node *plain_points = plain->points;
        
        // ova strana sad vise nema tacaka
        plain->points = NULL;
       
        // napravimo listu novih strana i njihovih suseda
        Node *new_plains = NULL, *new_plains_neighboors = NULL;
        for (Node *curr = get_neighboors(plain); curr != NULL; curr = curr->next){
            Plain *neighboor = (Plain *)curr->elem;

			// nadji tacke suseda
			Point *na, *nb, *nc;
			get_neighboors_points(plain, neighboor, &na, &nb, &nc);
			
            if (distance(*neighboor,*point) > 0){
                // stavi tacke u skup nerasporedjenih Tacaka
                plain_points = append_list(plain_points, neighboor->points);
               				
                // napravi nove trouglove na_point_nc i point_nb_nc
                new_plains = add_node(new_plains, make_plain(na, point, nc));
                new_plains = add_node(new_plains, make_plain(point, nb, nc));
                
                // dodaj susedove susede sa strana na_nc i nb_nc
                new_plains_neighboors = add_node(new_plains_neighboors,get_neighboor(neighboor,na,nc));
                new_plains_neighboors = add_node(new_plains_neighboors,get_neighboor(neighboor,nb,nc));
            } else {
                //  napravi novi trougao a_b_point
                new_plains = add_node(new_plains, make_plain(na, point, nb));
                
                // dodaj suseda sa strane a_b, gde, u new_plains_neighboors?
                new_plains_neighboors = add_node(new_plains_neighboors, neighboor);
                
                // pazi sad foricu -  nemora da se pravi pomocna promenjiva i ta sranja
            }
        }
        
        printf("\nofje2\n");
        
        // povezivanje suseda
        for (Node *i = new_plains; i != NULL; i = i->next){
            add_neighboors(i->elem, new_plains);
            add_neighboors(i->elem, new_plains_neighboors);
        }

        printf("\nofje3\n");
        
        for (Node *i = new_plains_neighboors; i != NULL; i = i->next){
			Plain *plain = (Plain *)i->elem;
			
			printf("susedi pre %d %d %d\n", plain->ba, plain->ac, plain->cb);
            add_neighboors(i->elem,new_plains);
			printf("susedi pos %d %d %d\n", plain->ba, plain->ac, plain->cb);
        }

        printf("\nofje4\n");
        
        // rasporedjivanje tacaka iz plain_points na new_plains

		arrange_points(new_plains, plain_points);

		 printf("\nofje4.5\n");
		
        // dodamo new_plains na kraj liste plains
        plains = append_list(plains, new_plains);
		
		printf("\nofje5\n");
    }

    return plains;
}

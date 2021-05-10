
class A {

    public void m () {
        System.out.println("A::m");
    }

};


class B extends A {

    public void m () {
        System.out.println("B::m");
    }

};


public class p {

    public static void f1 (A x) {
        x.m();
    }


    public static void f2 (B x) {
        x.m();
    }


    public static void main(String[] args) {
        A a = new A();
        a.m();

        B b = new B();
        b.m();

        A c = new B();
        c.m();

        System.out.println();

        f1(a);
        f1(b);
        f1(c);

        System.out.println();

        // f2(a);   //no pot compilar perquè espera una B, no una A.
        f2((B)a);   //peta en execució perquè a no és B
        f2(b);
        // f2(c);   //no pot compilar perquè espera una B, no una A.
        f2((B)c);   //no pot compilar perquè espera una B, no una A.

        System.out.println();

        A[] v = {a, b, c};
        for (A x : v) x.m();
    }
}

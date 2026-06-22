package design;
import java.util.ArrayList;

// 读者类
class Reader {
    private String name;
    private String cardNumber;
    private ArrayList<String> borrowedBooksIsbn;
    private int borrowedBooksCount;

    public Reader(String name, String cardNumber) {
        this.name = name;
        this.cardNumber = cardNumber;
        this.borrowedBooksIsbn = new ArrayList<>();
        this.borrowedBooksCount = 0;
    }

    // 各属性的getter和setter方法
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getCardNumber() {
        return cardNumber;
    }

    public void setCardNumber(String cardNumber) {
        this.cardNumber = cardNumber;
    }

    public ArrayList<String> getBorrowedBooksIsbn() {
        return borrowedBooksIsbn;
    }

    public void setBorrowedBooksIsbn(ArrayList<String> borrowedBooksIsbn) {
        this.borrowedBooksIsbn = borrowedBooksIsbn;
    }

    public int getBorrowedBooksCount() {
        return borrowedBooksCount;
    }

    public void setBorrowedBooksCount(int borrowedBooksCount) {
        this.borrowedBooksCount = borrowedBooksCount;
    }
}

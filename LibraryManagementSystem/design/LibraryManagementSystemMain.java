package design;
import java.util.Scanner;

public class LibraryManagementSystemMain {
    public static void main(String[] args) {
        LibraryManagementSystem library = new LibraryManagementSystem();
        Scanner scanner = new Scanner(System.in);

        // 初始化一些图书和读者数据
        Book book1 = new Book("Java从入门到精通", "张三", "清华大学出版社", "9787302567890", 1);
        Book book2 = new Book("数据结构与算法", "李四", "北京大学出版社", "9787301456789", 1);
        Reader reader1 = new Reader("王五", "123456");
        Reader reader2 = new Reader("赵六", "789012");

        library.addBook(book1);
        library.addBook(book2);
        library.addReader(reader1);
        library.addReader(reader2);

        boolean exit = false;
        while (!exit) {
            System.out.println("请选择操作：");
            System.out.println("1. 入库图书");
            System.out.println("2. 出库图书");
            System.out.println("3. 查询图书");
            System.out.println("4. 读者借书");
            System.out.println("5. 读者还书");
            System.out.println("6. 当前库存图书");
            System.out.println("7. 所有读者信息");
            System.out.println("8. 新增读者");  // 新增的选项
            System.out.println("9. 退出");
            int choice = scanner.nextInt();

            switch (choice) {
                case 1:
                    System.out.println("请输入图书信息（书名 作者 出版社 ISBN 库存数量）：");
                    String title = scanner.next();
                    String author = scanner.next();
                    String publisher = scanner.next();
                    String isbn = scanner.next();
                    int stockQuantity = scanner.nextInt();
                    Book newBook = new Book(title, author, publisher, isbn, stockQuantity);
                    library.addBook(newBook);
                    break;
                case 2:
                    System.out.println("请输入要出库的图书ISBN：");
                    String removeIsbn = scanner.next();
                    library.removeBook(removeIsbn);
                    break;
                case 3:
                    System.out.println("请输入查询关键词（书名、作者或ISBN）：");
                    String keyword = scanner.next();
                    library.searchBooks(keyword);
                    break;
                case 4:
                    System.out.println("请输入读者借阅证号和要借阅的图书ISBN：");
                    String cardNumber = scanner.next();
                    String borrowIsbn = scanner.next();
                    library.borrowBook(cardNumber, borrowIsbn);
                    break;
                case 5:
                    System.out.println("请输入读者借阅证号和要归还的图书ISBN：");
                    String returnCardNumber = scanner.next();
                    String returnIsbn = scanner.next();
                    library.returnBook(returnCardNumber, returnIsbn);
                    break;
                case 6:
                    library.listBooks();
                    break;
                case 7:
                    library.listReaders();
                    break;
                case 8:  // 新增读者的功能实现
                    System.out.println("请输入读者姓名和借阅证号：");
                    String name = scanner.next();
                    String newCardNumber = scanner.next();
                    Reader newReader = new Reader(name, newCardNumber);
                    library.addReader(newReader);
                    break;
                case 9:
                    exit = true;
                    System.out.println("已退出本系统。");
                    break;
                default:
                    System.out.println("无效的操作选择。");
            }
        }
        scanner.close();
    }
}
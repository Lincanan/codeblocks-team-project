package design;
import java.util.ArrayList;

// 图书馆图书管理系统类
class LibraryManagementSystem {
    private ArrayList<Book> books;
    private ArrayList<Reader> readers;

    public LibraryManagementSystem() {
        books = new ArrayList<>();
        readers = new ArrayList<>();
    }

    // 图书入库功能
    public void addBook(Book book) {
        Book existBook = findBook(book.getIsbn());
        if (existBook == null) {
            books.add(book);
            System.out.println("已成功入库图书: " + book.getTitle());
            return;
        }
        if (existBook.getAuthor().equals(book.getAuthor())
                && existBook.getTitle().equals(book.getTitle())
                && existBook.getPublisher().equals(book.getPublisher())) {
            existBook.setStockQuantity(existBook.getStockQuantity() + book.getStockQuantity());
            System.out.println("已成功入库图书: " + book.getTitle());
        } else {
            System.out.println("该isbn在图书馆中已存在，但新增图书与已存在图书的其他字段不一致，无法入库该图书: " + book.getTitle());
        }
    }

    // 图书出库功能（包括标记丢失等情况，这里简单模拟减少馆藏数量）
    public void removeBook(String isbn) {
        for (Book book : books) {
            if (book.getIsbn().equals(isbn)) {
                if (book.getStockQuantity() > 0) {
                    book.setStockQuantity(book.getStockQuantity() - 1);
                    System.out.println("图书已出库: " + book.getTitle());
                } else {
                    System.out.println("该图书库存为空，无法出库。");
                }
                return;
            }
        }
        System.out.println("未找到指定ISBN的图书。");
    }

    // 按多种条件查询图书功能
    public void searchBooks(String keyword) {
        System.out.println("查询结果:");
        for (Book book : books) {
            if (book.getTitle().contains(keyword) || book.getAuthor().contains(keyword) || book.getIsbn().contains(keyword)) {
                System.out.println("书名: " + book.getTitle() + ", 作者: " + book.getAuthor() + ", ISBN: " + book.getIsbn() + ", 库存: " + book.getStockQuantity());
            }
        }
    }

    // 添加读者功能
    public void addReader(Reader reader) {
        //readers.add(reader);
        //System.out.println("已成功添加读者: " + reader.getName());

        Reader existReader = findReader(reader.getCardNumber());
        if (existReader == null) {
            readers.add(reader);
            System.out.println("已成功添加读者: " + reader.getName()+"  "+reader.getCardNumber());
        } else {
            System.out.println("该读者借阅证号(cardNumber) "+ reader.getCardNumber()+" 已存在，请勿重复添加");
        }
    }

    // 读者借阅图书功能
    public void borrowBook(String cardNumber, String isbn) {
        Reader reader = findReader(cardNumber);
        if (reader != null) {
            Book book = findBook(isbn);
            if (book != null) {
                if (book.getStockQuantity() > 0 && reader.getBorrowedBooksCount() < 3 && !reader.getBorrowedBooksIsbn().contains(isbn)) {
                    book.setStockQuantity(book.getStockQuantity() - 1);
                    reader.getBorrowedBooksIsbn().add(isbn);
                    reader.setBorrowedBooksCount(reader.getBorrowedBooksCount() + 1);
                    System.out.println("借阅成功，读者 " + reader.getName() + " 借阅了图书 " + book.getTitle());
                } else if (reader.getBorrowedBooksCount() >= 3) {
                    System.out.println("读者已达到借阅上限，无法借阅更多图书。");
                } else if (reader.getBorrowedBooksIsbn().contains(isbn)) {
                    System.out.println("该读者已借此书，请勿重复借");
                } else {
                    System.out.println("该图书库存为空，无法借阅。");
                }
            } else {
                System.out.println("未找到指定ISBN的图书。");
            }
        } else {
            System.out.println("未找到指定借阅证号的读者。");
        }
    }

    // 读者归还图书功能
    public void returnBook(String cardNumber, String isbn) {
        Reader reader = findReader(cardNumber);
        if (reader != null) {
            if (reader.getBorrowedBooksIsbn().contains(isbn)) {
                Book book = findBook(isbn);
                if (book != null) {
                    book.setStockQuantity(book.getStockQuantity() + 1);
                    reader.getBorrowedBooksIsbn().remove(isbn);
                    reader.setBorrowedBooksCount(reader.getBorrowedBooksCount() - 1);
                    System.out.println("归还成功，读者 " + reader.getName() + " 归还了图书 " + book.getTitle());
                } else {
                    System.out.println("未找到指定ISBN的图书。");
                }
            } else {
                System.out.println("该读者并未借此书，无法归还");
            }
        } else {
            System.out.println("无此读者，无法执行归还操作");
        }
    }

    // 辅助方法：根据借阅证号查找读者
    private Reader findReader(String cardNumber) {
        for (Reader reader : readers) {
            if (reader.getCardNumber().equals(cardNumber)) {
                return reader;
            }
        }
        return null;
    }

    // 辅助方法：根据ISBN查找图书
    private Book findBook(String isbn) {
        for (Book book : books) {
            if (book.getIsbn().equals(isbn)) {
                return book;
            }
        }
        return null;
    }

    // 给出图书列表功能
    public void listBooks() {
        if (books.isEmpty()) {
        }
        System.out.println("当前库存图书：");
        for (Book book : books) {
            System.out.println("书名: " + book.getTitle() + ", 作者: " + book.getAuthor() + ", ISBN: " + book.getIsbn() + ", 库存: " + book.getStockQuantity() + ", 出版社: " + book.getPublisher());
        }
    }

    // 给出读者列表功能
    public void listReaders() {
        if (readers.isEmpty()) {
        }
        System.out.println("读者列表：");
        for (Reader reader : readers) {
            System.out.println("读者姓名: " + reader.getName() + ", 借阅证号: " + reader.getCardNumber() + ", 已借图书列表: " + reader.getBorrowedBooksIsbn() + ", 已借图书本数: " + reader.getBorrowedBooksCount());
        }
    }
}
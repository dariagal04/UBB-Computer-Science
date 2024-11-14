package src.ubb.domain;

import java.time.LocalDateTime;
import static java.lang.Math.max;
import static java.lang.Math.min;


public class Prietenie extends src.ubb.domain.Entity<Long> {


    Long UserId1, UserId2;

    public Prietenie(Long UserId1, Long UserId2) {
        this.UserId1 = min(UserId1, UserId2);
        this.UserId2 = max(UserId1, UserId2);
    }

    public Prietenie(src.ubb.domain.Tuple<String, String> tuple) {
        super();
    }

    public Long getUserId1() {
        return UserId1;
    }

    public Long getUserId2() {
        return UserId2;
    }

}

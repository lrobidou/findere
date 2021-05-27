
pdf(file="fpr_time_wrt_K.pdf",width=11,height=8)
resetPar <- function() {
  dev.new()
  op <- par(no.readonly = TRUE)
  dev.off()
  op
}
resetPar()

setwd("~/workspace/findere/paper_companion/HMP_analyses/wrt_K")
dev.new()


data = read.table("data_wrtK.txt", head=T)
dev.off()
par(mar=c(5,5,5,5))
plot(data$FPR~data$K,xlab="K value",ylab="FP rate (%)", lwd=2, pch=15, col="red", 
      type="o",  mgp=c(3,1,0), cex=2, ylim=c(0,0.3),  main="Query time & False positive rate, depending on K", cex.main = 2, cex.lab = 2, cex.axis = 2)


# TIME
par(new = TRUE, mgp=c(3,1,0))
plot(data$time~data$K,type="b",axes=FALSE,xlab="",ylab="",pch=19, cex=2, col="black", ylim=c(0,40), lty=2)

axis(4, ylim=c(0,40), las=1, cex.lab=2, mgp=c(3,1,0), cex.axis = 2)
mtext("Query time (s)", side=4, line=3.5, cex=2)

legend( x="topleft", 
        legend=c("findere FPR", "findere query time (s)"), cex = 2,
        col=c("red","black"), lty=c(1,2),
        pch=c(15,19), lwd=1,merge=TRUE, bty = "n")


dev.off()





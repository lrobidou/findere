
pdf(file="fpr_time_wrt_K.pdf",width=11,height=7)
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
# par(cex=1, mai=c(0.1,0.1,0.2,0.1))
par(fig=c(0,1,0.4,1), mar = par("mar") + c(0, 1, 0, 0))
plot(data$FPR~data$K,xlab="",ylab="FP rate (%)", lwd=2, pch=15, col="black", 
      type="o",  mgp=c(3,1,0), cex=2, ylim=c(0,0.2),  cex.main = 2, cex.lab = 2, cex.axis = 2)
mtext("findere results depending on K", side=3, line=1, cex=2)

legend( x="topleft", 
        legend=c("FPR"), cex = 2,
        col=c("black"), lty=c(1,2),
        pch=c(15), lwd=1,merge=TRUE, bty = "n")

# TIME

par(fig=c(0,1,0,0.6), new = TRUE)
plot(data$time~data$K,xlab="K value",ylab="Query time (s)", lwd=2, pch=15, col="black", 
     type="o",  mgp=c(3,1,0), cex=2, ylim=c(0,30),  cex.main = 2, cex.lab = 2, cex.axis = 2)

legend( x="topleft", 
        legend=c("query time"), cex = 2,
        col=c("black"), lty=c(1,2),
        pch=c(15), lwd=1,merge=TRUE, bty = "n")






dev.off()





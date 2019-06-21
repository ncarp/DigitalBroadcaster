
-- =============================================
-- Author:		<Pedro Roque, High Precision>
-- Create date: <2007-12-03>
-- Description:	<Add a new Artist, and returns the ID>
-- =============================================
CREATE PROCEDURE [dbo].[ArtistAdd]
	@Name char(100), 
	@ArtistID int = 0 output 
AS
BEGIN
	INSERT INTO Artists ([Name],[Activ]) VALUES (@Name,1)
	SET @ArtistID = Scope_Identity();
END

